/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:04 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:17:05 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			&& (token->name[*i + 1] != quote_char)
			&& token->name[*i + 1] != ' ' && quote_char == '"')
			*str = append_content(msh, &token, *str, i);
		else
			*str = append_letter_unquoted(token, *str, i);
	}
	if (token->name[*i] == quote_char)
		(*i)++;
}

int	is_export_assignment(t_token *current, t_token **head)
{
	t_token	*temp;

	if (!current || current->type != ARG)
		return (0);
	temp = *head;
	while (temp && temp != current)
	{
		if (temp->type == CMD && ft_strcmp(temp->name, "export") == 0)
		{
			if (ft_strchr(current->name, '='))
				return (1);
			return (0);
		}
		else if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (0);
}
