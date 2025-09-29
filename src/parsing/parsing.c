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
	set_command(token);
	if (!init_shell_data(mshell, token))
		return (0);
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
		if (try_expand_tilde(mshell, current))
			;
		else if (current->type == ARG || current->type == CMD
			|| current->type == FLAG || current->type == OUTFILE
			|| current->type == INFILE)
		{
			if (is_export_assignment(current, token))
			{
				expand_export_assignment(mshell, current);
			}
			else if (current->has_quote || ft_strchr(current->name, ' '))
				expand_quoted_token(mshell, current);
			else
				expand_unquoted(mshell, &current, token);
		}
		current = next;
	}
}

int	try_expand_tilde(t_shell *mshell, t_token *current)
{
	t_envp	*node;

	if (ft_strcmp(current->name, "~") == 0
		|| ft_strncmp(current->name, "~/", 2) == 0)
	{
		node = find_envp(mshell->env_list, "HOME");
		if (!node)
			return (1);
		free(current->name);
		current->name = ft_strdup(node->content);
		return (1);
	}
	return (0);
}

void	expand_unquoted(t_shell *mshell, t_token **current, t_token **head)
{
	char	*expanded;
	char	**arr;
	t_token	*next;

	expanded = expand_token_content(mshell, *current);
	next = (*current)->next;
	if (remove_if_empty(expanded, NULL, current, head))
		return ;
	arr = ft_split(expanded, ' ');
	free(expanded);
	if (remove_if_empty(NULL, arr, current, head))
		return ;
	free((*current)->name);
	(*current)->name = ft_strdup(arr[0]);
	(*current)->next = next;
	if (arr && arr[0])
		add_split_tokens(current, next, arr);
	free_arr(arr);
}

void	add_split_tokens(t_token **current, t_token *next, char **arr)
{
	int		i;
	t_token	*new;

	i = 1;
	while (arr[i])
	{
		new = ft_newtoken(arr[i]);
		new->type = (*current)->type;
		new->has_quote = false;
		new->next = next;
		if (next)
			next->prev = new;
		new->prev = (*current);
		(*current)->next = new;
		(*current) = new;
		i++;
	}
}
