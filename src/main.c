#include "../includes/minishell.h"

static void	run_shell(t_shell *mshell, t_token **token)
{
	while (true)
	{
		mshell->rd_l = readline("42minishell>> ");
		if (mshell->rd_l)
			add_history(mshell->rd_l);
		split_rdline(mshell, token);
		if (ft_strcmp(mshell->rd_l, "exit") == 0)
		{
			free_list(token);
			free(mshell->rd_l);
			break ;
		}
		free_list(token);
		free(mshell->rd_l);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	(void)ac;
	(void)av;
	(void)envp;
	i = 0;
	t_shell	mshell;
	t_token *token;

	token = NULL;
	ft_memset(&mshell, 0, sizeof(t_shell));
	run_shell(&mshell, &token);
	return (0);
}
