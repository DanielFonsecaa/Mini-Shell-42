#ifndef FREE_H
# define FREE_H

void	free_list(t_token **token);
void	error_shell(t_shell *mshell, t_token **token);
void	free_all(t_shell *mshell, t_token **token);
void	free_envp_list(t_envp *list);
void	free_envp_content(char *name, char *content);
void	free_arr(char **arr);
void    free_cmd_struct(t_shell *mshell);
void	handle_error_shell(t_shell *mshell, t_token **token);
void	close_fds(int **pipes, int num_pipes, int fd_in, int fd_out);
void	cleanup_pipes(int **pipes, int num_pipes, t_shell *mshell);

#endif