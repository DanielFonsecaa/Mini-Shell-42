#include "../../includes/minishell.h"

//debug arr of cmd --- erase latetr
static void	print_cmd_arr(t_shell *mshell)
{
	int		i;
	int		j;
	t_cmd	**cmd;

	cmd = mshell->command;
	i = -1;
	while (cmd[++i])
	{
		ft_printf_fd(1, " name -> %s\n", cmd[i]->name);
		j = -1;
		if (cmd[i]->flags)
		{
			while (cmd[i]->flags[++j])
				ft_printf_fd(1, " flag %d -> %s\n", j, cmd[i]->flags[j]);
		}
		j = -1;
		if (cmd[i]->args)
		{
			while (cmd[i]->args[++j])
				ft_printf_fd(1, " arg %d -> %s\n", j, cmd[i]->args[j]);
		}
	}
}

/**
 * @brief Parses the command line input and processes tokens for the minishell
 * 
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to the token list that will be populated
 */
int	parsing(t_shell *mshell, t_token **token)
{
	if (!quote_checker(mshell->rd_l))
	{
		mshell->exit_code = 2;
		return (ft_printf_fd(2, ERR_QUOTE), 0);
	}
	if (!tokenize(mshell->rd_l, token))
	{
		mshell->exit_code = 2;
		return (0);
	}
	init_token_data(mshell, token);
	expansion(mshell, token);
	if (!init_shell_data(mshell, token))
	{
		mshell->exit_code = 2;
		return (0);
	}
	print_cmd_arr(mshell);
	return (1);
}

void	expansion(t_shell *mshell, t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		if (current->type == ARG)
		{
			if (current->has_quote)
				expand_quoted_token(mshell, current);
			else
				expand_unquoted(mshell, &current, token);
		}
		current = next;
	}
}

void	expand_quoted_token(t_shell *mshell, t_token *token)
{
	char	*new_str;
	int		i;
	char quote_char;

	i = 0;
	new_str = safe_calloc(1, sizeof(char));
	while (token->name[i])
	{
		// Handle quotes first - but don't skip over content
		if (token->name[i] == '"' || token->name[i] == '\'')
		{
			quote_char = token->name[i];
			i++; // Skip opening quote
			
			// Process content inside quotes
			while (token->name[i] && token->name[i] != quote_char)
			{
				if (token->name[i] == '$' && token->name[i + 1] == '?' && quote_char == '"')
					new_str = append_exit_code(mshell, new_str, &i);
				else if (token->name[i] == '$' && quote_char == '"')
					// Only expand in double quotes, not single quotes
					new_str = append_content(mshell, &token, new_str, &i);
				else
				{
					char tmp[2] = {token->name[i], 0};
					new_str = ft_strjoin_free(new_str, tmp);
					i++;
				}
			}
			
			// Skip closing quote
			if (token->name[i] == quote_char)
				i++;
		}
		else if (token->name[i] == '$' && token->name[i + 1] == '?')
			new_str = append_exit_code(mshell, new_str, &i);
		else if (token->name[i] == '$')
			new_str = append_content(mshell, &token, new_str, &i);
		else
		{
			char tmp[2] = {token->name[i], 0};
			new_str = ft_strjoin_free(new_str, tmp);
			i++;
		}
	}
	free(token->name);
	token->name = new_str;
}

void	expand_unquoted(t_shell *mshell, t_token **current, t_token **head)
{
	char	*expanded;
	char	**arr;
	t_token	*next;
	t_token	*new;
	int		i;

	expanded = expand_token_content(mshell, *current);
	next = (*current)->next;
	if (!expanded)
	{
		remove_token_from_list(current, head);
	}
	arr = ft_split(expanded, ' ');
	free(expanded);
	free((*current)->name);
	(*current)->name = ft_strdup(arr[0]);
	(*current)->next = next;
	i = 1;
	while (arr[i])
	{
		new = ft_newtoken(arr[i]);
		new->type = (*current)->type;
		new->has_quote = false;
		new->next = (*current)->next;
		(*current)->next = new;
		(*current) = new;
		i++;
	}
	free_arr(arr);
}

void	remove_token_from_list(t_token **current, t_token **head)
{
	t_token	*prev;

	if (*current == *head)
	{
		*head = (*current)->next;
		free((*current)->name);
		free(*current);
		*current = *head;
		return;
	}
	prev = *head;
	while (prev && prev->next != *current)
		prev = prev->next;
	if (prev)
	{
		prev->next = (*current)->next;
		free((*current)->name);
		free(*current);
		*current = prev->next;
	}
}


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
		else if (token->name[i] == '$' && token->type == ARG)
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

char	*append_letter(t_token **token, char *new_str, int *i)
{
	char	tmp[2];
	char	quote_char;

	// Handle quote removal during expansion
	if (((*token)->name[*i] == '"' || (*token)->name[*i] == '\''))
	{
		quote_char = (*token)->name[*i];
		(*i)++; // Skip opening quote
		
		// Copy content inside quotes
		while ((*token)->name[*i] && (*token)->name[*i] != quote_char)
		{
			tmp[0] = (*token)->name[*i];
			tmp[1] = 0;
			new_str = ft_strjoin_free(new_str, tmp);
			(*i)++;
		}
		
		// Skip closing quote if found
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
