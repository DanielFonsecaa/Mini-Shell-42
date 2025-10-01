/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:16 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:39:16 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles the unset command to remove an environment variable.
 *
 * @param mshell Pointer to the shell structure.
 * @param token Pointer to the token list, where the next token is the variable
 */
void	handle_unset(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_envp	*node;

	if (!token || !*token || !(*token)->next)
		return ;
	temp = (*token)->next;
	if (check_for_flags(mshell))
		return ;
	while (temp)
	{
		node = find_envp(mshell->env_list, temp->name);
		if (node)
			remove_envp_var(&(mshell->env_list), node);
		temp = temp->next;
	}
	mshell->exit_code = 0;
}

/**
 * @brief Removes a node from the environment variable linked list.
 *
 * @param head Pointer to the head of the environment variable list.
 * @param node Pointer to the node to be removed.
 */
void	remove_envp_var(t_envp **head, t_envp *node)
{
	t_envp	*temp;

	temp = *head;
	if (ft_strcmp(temp->name, node->name) == 0)
	{
		*head = temp->next;
		free_strs(temp->name, temp->content);
		free(temp);
		temp = NULL;
		return ;
	}
	while (temp)
	{
		if (ft_strcmp(temp->next->name, node->name) == 0)
		{
			temp->next = node->next;
			free_strs(node->name, node->content);
			free(node);
			node = NULL;
			return ;
		}
		temp = temp->next;
	}
}
