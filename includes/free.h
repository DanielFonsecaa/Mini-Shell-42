#ifndef FREE_H
# define FREE_H

//Main free
void	free_all(t_shell *mshell, t_token **token);
void	handle_error_shell(t_shell *mshell, t_token **token);
void	handle_child_free(t_shell *mshell, t_token **token, char *path);

//free data
void	free_list(t_token **token);
void	free_envp_list(t_shell *mshell);
void	free_envp_content(char *name, char *content);
void	free_arr(char **arr);
void	free_cmd_struct(t_shell *mshell);

// free pipes and fds
void	close_fds(int **pipes, int num_pipes, int fd_in, int fd_out);
void	cleanup_pipes(int **pipes, int num_pipes, t_shell *mshell);

#endif