#include "../includes/minishell.h"

/**
 * @brief Runs the main shell loop, handling user input and command execution
 *
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to token structure for command parsing
 * @param envp Array of environment variables passed from main
 */
static void	run_shell(t_shell *mshell, t_token **token, char **envp)
{
	mshell->is_running = true;
	while (mshell->is_running)
	{
		mshell->env_var = ft_copy_envp(envp);
		getcwd(mshell->curr_wd, sizeof(mshell->curr_wd));
		mshell->fake_cwd = ft_strjoin(mshell->curr_wd, " 👉 ");
		mshell->rd_l = readline(mshell->fake_cwd);
		if (mshell->rd_l)
			add_history(mshell->rd_l);
		if (!parsing(mshell, token))
		{
			free_all(mshell, token);
			continue ;
		}
		execute(mshell, token);
/*		if (ft_strcmp(mshell->rd_l, "exit") == 0)
			mshell->is_running = false;*/
		free_all(mshell, token);
	}
}

/**
 * @brief Entry point of the minishell program
 * 
 * @param ac Number of command line arguments (unused)
 * @param av Array of command line argument strings (unused)
 * @param envp Array of environment variable strings
 * @return int Always returns 0 on successful completion
 */
int	main(int ac, char **av, char **envp)
{
	t_shell	mshell;
	t_token	*token;

	(void)ac;
	(void)av;
	token = NULL;
	ft_memset(&mshell, 0, sizeof(t_shell));
	run_shell(&mshell, &token, envp);
	return (mshell.exit_code);
}
