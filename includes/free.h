#ifndef FREE_H
# define FREE_H

void	free_list(t_token **token);
void	error_shell(t_shell *mshell, t_token **token);
void	free_all(t_shell *mshell, t_token **token);
void	free_envp_list(t_envp *list);
void	free_envp_content(char *name, char *content);
void	free_arr(char **arr);
void    free_cmd_struct(t_shell *mshell);

#endif
