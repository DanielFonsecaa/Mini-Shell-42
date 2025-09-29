#include "../../includes/minishell.h"

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
}

/**
 * @brief Sets up signal handling for the minishell program
 */
void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_sigpipe);
}

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}
