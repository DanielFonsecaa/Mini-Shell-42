#include "../includes/minishell.h"

void    handle_ctrl_c(int sig)
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

void handle_ctrl_c_child(int sig)
{
	if (sig == SIGINT && g_sig)
		ft_printf_fd(1, "\n");
}

void    handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
}