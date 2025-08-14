#include "../../includes/minishell.h"

void	execute_pipeline(t_shell *mshell, t_token **token)
{
	(void)token;
	int	i;

	i = 0;
	while (i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			perror("fork");
			//	ft_fork_error(mshell);
		else if (mshell->pids[i] == 0)
		{
			setup_child(i, mshell->num_commands, mshell->pipes, mshell->fd);
			cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
//			if (h_d)
//				execute_final(argv[i + 3], envp, NULL);
			execute_final(mshell, token, mshell->command[i]);
			exit(127);
		}
		i++;
	}
	wait_and_get_exit_status(mshell);
	//free(mshell->pids);
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