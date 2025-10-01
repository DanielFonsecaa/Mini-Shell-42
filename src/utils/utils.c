/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:41:21 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:41:21 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Modifies the shell level environment variable by a specified value
 *
 * @param node Pointer to the environment variable linked list to search in
 * @param value Integer value to add to the current shell level
 */
void	modify_shell_level(t_envp *node, int value)
{
	t_envp	*existing_node;
	char	*str_level;
	char	*old_level;
	int		new_level;

	existing_node = find_envp(node, "SHLVL");
	if (!existing_node)
	{
		ft_printf_fd(2, ERR_SHLVLNOT_FOUND);
		return ;
	}
	old_level = existing_node->content;
	new_level = ft_atoi(old_level);
	str_level = ft_itoa(new_level + value);
	if (new_level >= 999)
	{
		ft_printf(BASH_1000, new_level + 1);
		str_level = ft_itoa(1);
	}
	existing_node->content = str_level;
	existing_node->exported = true;
	free(old_level);
}

int	handle_quote(char *str, int *start, int *in_quote, char *quote_char)
{
	if (!(*in_quote) && (str[*start] == '\'' || str[*start] == '"'))
	{
		*in_quote = 1;
		*quote_char = str[*start];
		(*start)++;
		return (1);
	}
	if (*in_quote && str[*start] == *quote_char)
	{
		*in_quote = 0;
		(*start)++;
		return (1);
	}
	return (0);
}

int	check_for_flags(t_shell *mshell)
{
	int	i;
	int	check;

	i = 0;
	while (mshell->command[i])
	{
		check = 0;
		if (!mshell->command[i]->args || !mshell->command[i]->args[check])
			return (0);
		while (mshell->command[i]->args[check])
		{
			if (mshell->command[i]->args[check][0] == '-')
			{
				mshell->exit_code = 1;
				ft_printf_fd(2, ERR_NO_FLAG_ALLOWED);
				return (1);
			}
			check++;
		}
		i++;
	}
	return (0);
}

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

int	skip_whitespace(char *str, int i)
{
	while (str[i] && ft_iswhite_space(str[i]))
		i++;
	return (i);
}
