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

static int	inside_single_quotes(char *str, int pos, int equals_index)
{
	int	i;
	int	single_quote_count;

	i = equals_index + 1;
	single_quote_count = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			single_quote_count++;
		i++;
	}
	return (single_quote_count % 2 == 1);
}

static int	init_vars_expand(int *i, int *equals_index, char **equals_pos, t_token *token)
{
	*i = 0;
	*equals_pos = ft_strchr(token->name, '=');
	if (!*equals_pos)
		return (0);
	*equals_index = *equals_pos - token->name;
	return (1);
}

static void exit_code_or_append(t_shell *mshell, t_token *token, char **new_str, int *i)
{
    if (token->name[*i + 1] == '?')
				*new_str = append_exit_code(mshell, *new_str, i);
			else
				*new_str = append_content(mshell, &token, *new_str, i);
}

void	expand_export_assignment(t_shell *mshell, t_token *token)
{
	char	*new_str;
	char	*equals_pos;
	int		i;
	int		equals_index;

	init_vars_expand(&i, &equals_index, &equals_pos, token);
	new_str = safe_calloc(1, sizeof(char));
	while (token->name[i])
	{
		if (i > equals_index && (token->name[i] == '\'' || token->name[i] == '"'))
		{
			i++;
			continue;
		}
		if (i > equals_index && token->name[i] == '$'
			&& token->name[i + 1] && !inside_single_quotes(token->name, i, equals_index))
		{
			exit_code_or_append(mshell, token, &new_str, &i);
		}
		else
			new_str = append_letter_unquoted(token, new_str, &i);
	}
    free(token->name);
	token->name = new_str;
}
