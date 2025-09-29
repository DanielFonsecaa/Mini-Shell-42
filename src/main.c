#include "../includes/minishell.h"

int	g_sig;

/**
 * @brief Runs the main shell loop, handling user input and command execution
 *
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to token structure for command parsing
 * @param envp Array of environment variables passed from main
 */
static void	run_shell(t_shell *mshell, t_token **token)
{
	while (mshell->is_running)
	{
		init_shell_envp_cwd(mshell);
		mshell->rd_l = readline(mshell->fake_cwd);
		if (mshell->rd_l && mshell->rd_l[0])
			add_history(mshell->rd_l);
		if (g_sig == 130)
			mshell->exit_code = 130;
		if (g_sig == 141)
		{
			mshell->exit_code = 0;
			g_sig = 0;
		}
		if (!mshell->rd_l)
		{
			ft_printf("exit\n");
			handle_error_shell(mshell, token);
			exit(mshell->exit_code);
		}
		if (!mshell->rd_l[0] || !parsing(mshell, token))
		{
			free_all(mshell, token);
			continue ;
		}
		execute_cmd_line(mshell, token);
		free_all(mshell, token);
		g_sig = 0;
	}
	modify_shell_level(mshell->env_list, -1);
	free_envp_list(mshell);
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
	mshell.is_running = true;
	create_envp_list(&(mshell.env_list), envp);
	modify_shell_level(mshell.env_list, 1);
	handle_signal();
	run_shell(&mshell, &token);
	return (mshell.exit_code);
}
