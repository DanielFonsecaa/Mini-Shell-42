#ifndef BUILT_INS_H
# define BUILT_INS_H

// Built ins handler
void	handle_pwd(t_shell *mshell, t_token **token);
void	handle_env(t_shell *mshell);
void	handle_exit(t_shell *mshell, t_token **token);

// Utils
int		is_built_in(t_token **token);
int		verify_num(char *value);

#endif
