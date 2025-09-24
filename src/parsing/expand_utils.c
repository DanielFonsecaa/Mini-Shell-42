#include "../../includes/minishell.h"

char	*expand_token_content(t_shell *mshell, t_token *token)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = safe_calloc(ft_strlen(token->name) + 1, sizeof(char));
	while (token->name[i])
	{
		if (token->name[i] == '$' && token->name[i + 1] == '?'
			&& token->type == ARG)
			new_str = append_exit_code(mshell, new_str, &i);
		else if (token->name[i] == '$' && token->name[i + 1])
			new_str = append_content(mshell, &token, new_str, &i);
		else
			new_str = append_letter_unquoted(token, new_str, &i);
	}
	return (new_str);
}

char	*append_exit_code(t_shell *mshell, char *new_str, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(mshell->exit_code);
	new_str = ft_strjoin_free(new_str, exit_code);
	free(exit_code);
	*i += 2;
	return (new_str);
}

char	*append_content(t_shell *mshell, t_token **token, char *str, int *i)
{
	t_envp	*node;
	char	*variable;
	char	*new_content;
	int		start;
	int		len;
	char	tmp[2];

	start = *i + 1;
	len = 0;
	if (ft_isdigit((*token)->name[start]))
	{
		len = 1;
		str = ft_strjoin_free(str, "");
		*i = start + len;
		return (str);
	}
	if ((*token)->name[start] == '!' || (*token)->name[start] == '#'
		|| (*token)->name[start] == '$' || (*token)->name[start] == '*'
		|| (*token)->name[start] == '@' || (*token)->name[start] == '-')
	{
		len = 1;
		str = ft_strjoin_free(str, "");
		*i = start + len;
		return (str);
	}
	if (!ft_isalpha((*token)->name[start]) && (*token)->name[start] != '_')
	{
		tmp[0] = '$';
		tmp[1] = '\0';
		str = ft_strjoin_free(str, tmp);
		*i = start;
		return (str);
	}
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

char	*append_letter(t_token **token, char *new_str, int *i)
{
	char	tmp[2];
	char	quote_char;

	if (((*token)->name[*i] == '"' || (*token)->name[*i] == '\''))
	{
		quote_char = (*token)->name[*i];
		(*i)++;
		while ((*token)->name[*i] && (*token)->name[*i] != quote_char)
		{
			tmp[0] = (*token)->name[*i];
			tmp[1] = 0;
			new_str = ft_strjoin_free(new_str, tmp);
			(*i)++;
		}
		if ((*token)->name[*i] == quote_char)
			(*i)++;
	}
	else
	{
		tmp[0] = (*token)->name[*i];
		tmp[1] = 0;
		new_str = ft_strjoin_free(new_str, tmp);
		(*i)++;
	}
	return (new_str);
}

char	*append_letter_unquoted(t_token *token, char *new_str, int *i)
{
	char	tmp[2];

	tmp[0] = token->name[*i];
	tmp[1] = 0;
	new_str = ft_strjoin_free(new_str, tmp);
	(*i)++;
	return (new_str);
}
