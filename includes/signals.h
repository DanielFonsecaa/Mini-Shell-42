#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_signal(void);
void	handle_ctrl_c(int sig);
void	handle_ctrl_c_child(int sig);
void    handle_child(void);
void    handle_quit_child(int sig);

#endif
