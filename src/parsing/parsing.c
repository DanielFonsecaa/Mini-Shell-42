#include "../../includes/minishell.h"

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
	set_t_type(token);
	if (!init_shell_data(mshell, token))
	{
		mshell->exit_code = 1;
		return (0);
	}
	init_heredoc(mshell, token);
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
		if (current->type == ARG || current->type == CMD
			|| current->type == FLAG || current->type == OUTFILE
			|| current->type == INFILE)
		{
			if (current->has_quote || ft_strchr(current->name, ' '))
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

	i = 0;
	new_str = safe_calloc(1, sizeof(char));
	while (token->name[i])
	{
		if (token->name[i] == '"' || token->name[i] == '\'')
			expand_inside_quotes(token, mshell, &new_str, &i);
		else if (token->name[i] == '$' && token->name[i + 1] == '?')
			new_str = append_exit_code(mshell, new_str, &i);
		else if (token->name[i] == '$' && token->name[i + 1])
			new_str = append_content(mshell, &token, new_str, &i);
		else
			new_str = append_letter_unquoted(token, new_str, &i);
	}
	free(token->name);
	token->name = new_str;
}

void	expand_inside_quotes(t_token *token, t_shell *msh, char **str, int *i)
{
	char	quote_char;

	quote_char = token->name[*i];
	(*i)++;
	while (token->name[*i] && token->name[*i] != quote_char)
	{
		if (token->name[*i] == '$' && token->name[*i + 1]
			== '?' && quote_char == '"')
			*str = append_exit_code(msh, *str, i);
		else if (token->name[*i] == '$' && token->name[*i + 1]
			&& (token->name[*i + 1] != quote_char) && token->name[*i + 1] != ' ' && quote_char == '"')
			*str = append_content(msh, &token, *str, i);
		else
			*str = append_letter_unquoted(token, *str, i);
	}
	if (token->name[*i] == quote_char)
		(*i)++;
}

void	expand_unquoted(t_shell *mshell, t_token **current, t_token **head)
{
	char	*expanded;
	char	**arr;
	t_token	*next;

	expanded = expand_token_content(mshell, *current);
	next = (*current)->next;
	if (!expanded)
		remove_token_from_list(current, head);
	arr = ft_split(expanded, ' ');
	free(expanded);
	free((*current)->name);
	(*current)->name = ft_strdup(arr[0]);
	(*current)->next = next;
	if (arr && arr[0])
		add_split_tokens(current, next, arr);
	free_arr(arr);
}
