#include "../../includes/minishell.h"

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

void	handle_sigpipe(int sig)
{
	if (sig == SIGPIPE)
		g_sig = 141;
}
