#include "../../includes/minishell.h"

void	execute_pipeline(t_shell *mshell, t_token **token)
{
	(void)token;
	int	i;
	int status;
	i = 0;
	mshell->pids = safe_calloc(mshell->num_commands, sizeof(pid_t));
	while (i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			perror("fork");
			//	ft_fork_error(mshell);
		else if (mshell->pids[i] == 0)
		{
//			setup_child(i, mshell->num_cmds, mshell->pipes, mshell->fd);
//			cleanup_pipes(mshell->pipes, mshell->num_cmds - 1, mshell);
//			if (h_d)
//				execute_final(argv[i + 3], envp, NULL);
			execute_final(mshell->commands[i], mshell->env_var);
			exit(127);
		}
		i++;
	}
	i = 0;
	while (i < mshell->num_commands)
	{
		waitpid(mshell->pids[i], &status, 0);
		i++;
	}
}