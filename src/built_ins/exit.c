/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:11 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/02 10:01:32 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_exit_arg(t_shell *mshell, char *value, long long *status)
{
	if (!verify_num(value) || !ft_atoll(value, status))
	{
		mshell->exit_code = 2;
		ft_printf_fd(2, ERR_EXIT_NOT_NBR, value);
		mshell->is_running = false;
		return (0);
	}
	return (1);
}

static int	check_too_many_args(t_shell *mshell, t_token *temp)
{
	if (temp->next && temp->next->next && temp->next->next->type != PIPE)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		mshell->exit_code = 1;
		return (0);
	}
	return (1);
}

static void	set_exit_status(t_shell *mshell, t_token *temp, long long status)
{
	if (temp->next)
		mshell->exit_code = status % 256;
	mshell->is_running = false;
	ft_printf_fd(1, "exit\n");
}

void	handle_exit(t_shell *mshell, t_token **token)
{
	t_token		*temp;
	long long	status;
	char		*value;

	temp = *token;
	status = 0;
	if (temp->next && temp->next->type == PIPE)
		return ;
	if (temp->next)
	{
		value = temp->next->name;
		if (!validate_exit_arg(mshell, value, &status))
			return ;
	}
	if (!check_too_many_args(mshell, temp))
		return ;
	set_exit_status(mshell, temp, status);
}

/**
 * @brief Verifies if the given string is a valid number.
 * 
 * @param value The string to be checked.
 * @return int Returns 1 if is a valid number, 0 otherwise.
 */
int	verify_num(char *value)
{
	int	i;

	i = 0;
	if (ft_strlen(value) > 20 || !value || !*value)
		return (0);
	if (strcmp(value, "--") == 0)
		return (1);
	if (value[i] == '-' || value[i] == '+')
		i++;
	if (!value[i])
		return (0);
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}
