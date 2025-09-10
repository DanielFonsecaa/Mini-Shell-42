#include "../../includes/minishell.h"

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
		new->prev = (*current);
		(*current)->next = new;
		(*current) = new;
		i++;
	}
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
		return ;
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

/**
 * @brief Checks if a token represents a redirection operator
 *
 * @param temp Pointer to the token to be checked
 * @return int Returns 1 if the token is a redirection type, 0 if not
 */
int	check_redir_type(t_token *temp)
{
	return (temp->type == INFILE || temp->type == OUTFILE
		|| temp->type == HERE || temp->type == APPEND);
}

int	check_infile(t_token *token)
{
	int		fd;
	t_token	*temp;

	temp = token;
	fd = open(temp->next->name, O_RDONLY);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}
