#ifndef BUILT_INS_H
# define BUILT_INS_H

// Built ins handler
int	handle_pwd(t_token **token);
int	is_built_in(t_token **token);
int	handle_env(t_shell *mshell);

#endif
