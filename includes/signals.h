#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_signal(t_shell *mshell);
void	handle_ctrl_c(int sig);
void	handle_ctrl_c_child(int sig);

#endif
