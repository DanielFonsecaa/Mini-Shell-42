## Issues Fixed

### 1. Variable Expansion Edge Cases (Tests 186-210)

**Problem:** The shell was not handling bash-compatible variable expansion for special cases like positional parameters (`$42`), special shell parameters (`$!`), and invalid variable names (`$=`).

**Root Cause:** The `append_content()` function only checked for alphanumeric characters and underscores, without properly handling bash's special variable expansion rules.

### 2. Environment Variable Corruption (Test 265)

**Problem:** The `MANPAGER` environment variable was being corrupted during initialization, showing `"h -c '..."` instead of `"sh -c '..."`.

**Root Cause:** The `which_quote()` function was returning the first character of any string instead of only returning quote characters, causing `ft_strtrim_char()` to incorrectly trim non-quote characters.

---

## Changes Made

### Change 1: Variable Expansion Fix

**File:** `src/parsing/expand_utils.c`
**Function:** `append_content()`

**BEFORE:**

```c
char	*append_content(t_shell *mshell, t_token **token, char *str, int *i)
{
	t_envp	*node;
	char	*variable;
	char	*new_content;
	int		start;
	int		len;

	start = *i + 1;
	len = 0;
	while ((*token)->name[start + len])
	{
		if (!(ft_isalnum((*token)->name[start + len])
				|| (*token)->name[start + len] == '_'))
			break ;
		len++;
	}
	variable = ft_substr((*token)->name, start, len);
	node = find_envp(mshell->env_list, variable);
	if (node)
		new_content = node->content;
	else
		new_content = "";
	str = ft_strjoin_free(str, new_content);
	free(variable);
	*i = start + len;
	return (str);
}
```

**AFTER:**

```c
char	*append_content(t_shell *mshell, t_token **token, char *str, int *i)
{
	t_envp	*node;
	char	*variable;
	char	*new_content;
	int		start;
	int		len;

	start = *i + 1;
	len = 0;

	// Handle positional parameters ($0, $1, $2, etc.)
	if (ft_isdigit((*token)->name[start]))
	{
		len = 1;
		str = ft_strjoin_free(str, "");
		*i = start + len;
		return (str);
	}

	// Handle special shell parameters ($!, $#, $$, $*, $@, $-)
	if ((*token)->name[start] == '!' || (*token)->name[start] == '#'
		|| (*token)->name[start] == '$' || (*token)->name[start] == '*'
		|| (*token)->name[start] == '@' || (*token)->name[start] == '-')
	{
		len = 1;
		str = ft_strjoin_free(str, "");
		*i = start + len;
		return (str);
	}

	// Handle invalid variable names (treat as literal $)
	if (!ft_isalpha((*token)->name[start]) && (*token)->name[start] != '_')
	{
		char tmp[2];
		tmp[0] = '$';
		tmp[1] = '\0';
		str = ft_strjoin_free(str, tmp);
		*i = start;
		return (str);
	}

	// Handle normal environment variables
	while ((*token)->name[start + len])
	{
		if (!(ft_isalnum((*token)->name[start + len])
				|| (*token)->name[start + len] == '_'))
			break ;
		len++;
	}
	variable = ft_substr((*token)->name, start, len);
	node = find_envp(mshell->env_list, variable);
	if (node)
		new_content = node->content;
	else
		new_content = "";
	str = ft_strjoin_free(str, new_content);
	free(variable);
	*i = start + len;
	return (str);
}
```

### Change 2: Quote Detection Fix

**File:** `src/utils/utils.c`
**Function:** `which_quote()`

**BEFORE:**

```c
/**
 * @brief Determines which type of quote char is at the beginning of a string.
 *
 * @param str Pointer to the string to examine
 * @return char of the first character of the string
 */
char	which_quote(char *str)
{
	return (*str);
}
```

**AFTER:**

```c
/**
 * @brief Determines which type of quote char is at the beginning of a string.
 *
 * @param str Pointer to the string to examine
 * @return char The quote character if found, or 0 if no quote at start
 */
char	which_quote(char *str)
{
	if (str && (*str == '"' || *str == '\''))
		return (*str);
	return (0);
}
```

### Change 3: Environment Variable Creation Fix

**File:** `src/built_ins/export/utils_list_export.c`
**Function:** `create_node()`

**BEFORE:**

```c
t_envp	*create_node(char *name, char *content, bool exported)
{
	t_envp	*node;
	char	*new_content;

	if (!content)
		new_content = ft_strdup("");
	else if (has_quote(content))
		new_content = ft_strtrim_char(content, which_quote(content));
	else
		new_content = ft_strdup(content);
	node = safe_calloc(1, sizeof(t_envp));
	node->name = ft_strdup(name);
	node->content = new_content;
	node->exported = exported;
	node->next = NULL;
	return (node);
}
```

**AFTER:**

```c
t_envp	*create_node(char *name, char *content, bool exported)
{
	t_envp	*node;
	char	*new_content;
	char	quote_char;

	if (!content)
		new_content = ft_strdup("");
	else if (has_quote(content))
	{
		quote_char = which_quote(content);
		if (quote_char != 0)
			new_content = ft_strtrim_char(content, quote_char);
		else
			new_content = ft_strdup(content);
	}
	else
		new_content = ft_strdup(content);
	node = safe_calloc(1, sizeof(t_envp));
	node->name = ft_strdup(name);
	node->content = new_content;
	node->exported = exported;
	node->next = NULL;
	return (node);
}
```
