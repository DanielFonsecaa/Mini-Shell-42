/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:01 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:17:02 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//removed current = NULL before current = head in both ifs
void	remove_token_from_list(t_token **current, t_token **head)
{
	t_token	*prev;

	if (*current == *head)
	{
		*head = (*current)->next;
		free((*current)->name);
		free(*current);
		*current = *head;
		if (*current)
			(*current)->prev = NULL;
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
		if (current && prev)
			(*current)->prev = prev;
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
	char	*file;

	temp = token;
	file = NULL;
	if (temp->next->has_quote)
	{
		file = ft_strtrim_char(temp->next->name, which_quote(temp->next->name));
		fd = open(file, O_RDONLY);
		free(temp->next->name);
		temp->next->name = NULL;
		temp->next->name = file;
	}
	else
		fd = open(temp->next->name, O_RDONLY);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
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
