#include "../../includes/minishell.h"

void	execute_pipeline(t_shell *mshell, t_token **token)
{
	int	i;
	int	*fd_to_pass;

	i = -1;
	while (++i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			return (perror("fork"));
		if (mshell->pids[i] == 0)
		{
			fd_to_pass = NULL;
			if (mshell->fd[0] > 2 || mshell->fd[1] > 2)
				fd_to_pass = mshell->fd;
			setup_child(i, mshell->num_commands, mshell->pipes, fd_to_pass);
			execute_final(mshell, token, mshell->command[i]);
			exit(127);
		}
		if (i > 0)
			close(mshell->pipes[i-1][1]);
	}
	if (mshell->num_commands > 1)
		close(mshell->pipes[mshell->num_commands-2][0]);
	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
}

void	wait_and_get_exit_status(t_shell *mshell)
{
	int	i;
	int	status;

	i = 0;
	while (i < mshell->num_commands)
	{
		waitpid(mshell->pids[i], &status, 0);
		if (i == mshell->num_commands - 1)
		{
			if (WIFEXITED(status))
				mshell->exit_code = WEXITSTATUS(status);
			else
				mshell->exit_code = 1;
		}
		i++;
	}
}
