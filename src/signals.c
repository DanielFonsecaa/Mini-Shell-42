#include "../includes/minishell.h"
/**
 * @brief Signal handler for SIGINT (Ctrl+C) interruption
 *
 * @param sig The signal number received (expected to be SIGINT)
 * @note Re-registers the signal handler to maintain consistent behavior
 */
void	handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		ft_printf_fd(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, handle_ctrl_c);
	}
}

void	handle_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
}

/**
 * @brief Sets up signal handling for the minishell program
 */
void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Blocks signals in parent while child is executing
 */
void	block_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Restores signal handling after child execution
 */
void	restore_parent_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
