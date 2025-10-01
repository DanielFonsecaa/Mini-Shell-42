/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:28 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:39:28 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_command(t_token *token, int index)
{
	t_token	*temp;
	t_token	*group_start;
	int		current_group;

	temp = token;
	group_start = token;
	current_group = 0;
	if (index == 0)
		return (group_start);
	while (temp)
	{
		if (temp->type == PIPE)
		{
			current_group++;
			if (current_group == index && temp->next)
				return (temp->next);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	handle_single_command(t_shell *mshell, t_token **token, t_token *temp)
{
	int	std_in;
	int	std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	handle_redirections(mshell, token, temp);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

/**
 * @brief Waits for all child to complete and retrieves the exit status
 *        of the last command in the pipeline.
 *
 * @param mshell Pointer to the shell structure
 */
void	wait_and_get_exit_status(t_shell *mshell)
{
	int	i;
	int	status;

	block_parent_signals();
	i = 0;
	while (i < mshell->num_commands)
	{
		waitpid(mshell->pids[i], &status, 0);
		if (i == mshell->num_commands - 1)
			set_exitcode_status(mshell, status);
		i++;
	}
	restore_parent_signals();
}

void	set_exitcode_status(t_shell *mshell, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			mshell->exit_code = 130;
			ft_printf_fd(1, "\n");
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf_fd(1, "Quit (core dumped)\n");
			mshell->exit_code = 131;
		}
		else if (WTERMSIG(status) == SIGPIPE)
			mshell->exit_code = 0;
		else
			mshell->exit_code = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		mshell->exit_code = WEXITSTATUS(status);
	else
		mshell->exit_code = 1;
}

/**
 * @brief Cleans up resources and waits for child processes to complete
 *
 * @param mshell Pointer to the shell structure
 */
void	cleanup_and_wait(t_shell *mshell)
{
	int	i;

	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
	mshell->pipes = NULL;
	if (mshell->heredoc_fd && mshell->num_heredoc > 0)
	{
		i = 0;
		while (i < mshell->num_heredoc)
		{
			if (mshell->heredoc_fd[i] >= 0)
				close(mshell->heredoc_fd[i]);
			i++;
		}
		free(mshell->heredoc_fd);
		mshell->heredoc_fd = NULL;
		mshell->num_heredoc = 0;
	}
	if (mshell->pids)
		free(mshell->pids);
	mshell->pids = NULL;
}
