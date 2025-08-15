#include "../includes/minishell.h"

void    handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf_fd(1, "\n");
		rl_redisplay();
	}
}

void    handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
}