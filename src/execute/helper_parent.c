#include "../../includes/minishell.h"

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
	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
	mshell->pipes = NULL;
	if (mshell->pids)
		free(mshell->pids);
	mshell->pids = NULL;
}
