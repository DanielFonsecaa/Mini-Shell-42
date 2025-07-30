#include "../includes/minishell.h"

static void	run_shell(t_shell *mshell, t_token **token, char **envp)
{
	while (true)
	{
		mshell->env_var = ft_copy_envp(envp);
		getcwd(mshell->curr_wd, sizeof(mshell->curr_wd));
		mshell->fake_cwd = ft_strjoin(mshell->curr_wd, " >>");
		mshell->rd_l = readline(mshell->fake_cwd);
		if (mshell->rd_l)
			add_history(mshell->rd_l);
		split_rdline(mshell, token);
		if (ft_strcmp(mshell->rd_l, "exit") == 0)
		{
			free_loop(mshell, token);
			break ;
		}
		free_loop(mshell, token);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	mshell;
	t_token *token;

	token = NULL;
	ft_memset(&mshell, 0, sizeof(t_shell));
	run_shell(&mshell, &token, envp);
	return (0);
}
