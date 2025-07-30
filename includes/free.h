#ifndef FREE_H
# define FREE_H

void	free_list(t_token **token);
void	error_shell(t_shell *mshell, t_token **token);
void	free_all(t_shell *mshell, t_token **token);
void	free_envp(char **arr);

#endif
