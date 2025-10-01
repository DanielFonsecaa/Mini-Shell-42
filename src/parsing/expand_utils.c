/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:08 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:17:09 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_shell_var(char c)
{
	return (c == '!' || c == '#' || c == '$'
		||c == '*' || c == '@' || c == '-');
}

// Handles special/invalid variable cases, returns 1 if handled, 0 otherwise
int	handle_special_var_case(t_token **token, char **str, int *i, int start)
{
	char	tmp[2];

	if (ft_isdigit((*token)->name[start])
		|| is_special_shell_var((*token)->name[start]))
	{
		*str = ft_strjoin_free(*str, "");
		*i = start + 1;
		return (1);
	}
	if (!ft_isalpha((*token)->name[start]) && (*token)->name[start] != '_')
	{
		tmp[0] = '$';
		tmp[1] = '\0';
		*str = ft_strjoin_free(*str, tmp);
		*i = start;
		return (1);
	}
	return (0);
}

int	remove_if_empty(char *exp, char **arr, t_token **current, t_token **head)
{
	if ((exp && (!exp[0]) && (*current)->type == CMD
			&& (*current)->name[0] == '$'))
	{
		free(exp);
		remove_token_from_list(current, head);
		return (1);
	}
	if (arr && (!arr[0]) && (*current)->type == CMD
		&& (*current)->name[0] == '$')
	{
		free(arr);
		remove_token_from_list(current, head);
		return (1);
	}
	return (0);
}
