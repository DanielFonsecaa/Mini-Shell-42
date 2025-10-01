/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:08 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:39:08 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles the 'env' command
 * 
 * @param mshell Pointer to the shell structure
 * @param fd
 */
void	handle_env(t_shell *mshell, int fd, t_token **token)
{
	t_envp	*node;

	if (!mshell)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, ERR_COMPUTER_ERROR);
		return ;
	}
	if (!mshell->env_list)
	{
		mshell->exit_code = 1;
		return ;
	}
	if (check_for_args(mshell, token))
		return ;
	node = mshell->env_list;
	while (node)
	{
		if (node->exported)
			ft_printf_fd(fd, "%s=%s\n", node->name, node->content);
		node = node->next;
	}
	mshell->exit_code = 0;
}

int	check_for_args(t_shell *mshell, t_token **token)
{
	int		i;
	t_token	*temp;

	(void)mshell;
	i = 0;
	temp = *token;
	while (temp && temp->type != PIPE)
	{
		temp = temp->next;
		i++;
	}
	if (i > 1)
		return (1);
	return (0);
}
