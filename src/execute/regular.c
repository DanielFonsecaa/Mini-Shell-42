#include "../../includes/minishell.h"

void	execute_pipeline(t_shell *mshell, t_token **token)
{
	int	i;

	i = 0;
	while (i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
		{
			perror("fork");
			return ;
		}
		if (mshell->pids[i] == 0)
		{
			setup_child(i, mshell->num_commands, mshell->pipes, mshell->fd);
			execute_final(mshell, token, mshell->command[i]);
			exit(127);
		}
		i++;
	}
	for (int j = 0; j < mshell->num_commands - 1; j++)
	{
		close(mshell->pipes[j][0]);
		close(mshell->pipes[j][1]);
	}

	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
}

void wait_and_get_exit_status(t_shell *mshell)
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