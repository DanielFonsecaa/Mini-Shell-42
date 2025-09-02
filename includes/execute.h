#ifndef EXECUTE_H
# define EXECUTE_H

//Main execution
void execute_built_in(t_shell *mshell, t_token **token, int fd);
void execute_child_command(t_shell *mshell, t_token **token, t_cmd *command, int out_fd);
void	execute_cmd_line(t_shell *mshell, t_token **token);
void	execute_with_pipes_or_redirect(t_shell *mshell, t_token **token);
void execute_pipe_redirect(t_shell *mshell, t_token **token);

//Child related
void	format_cmd(t_shell *mshell, t_cmd *command);
char	*ft_get_path(char **envp, char *cmd);
void	setup_child(int index, int num_cmds, int **pipes, int *fd);

//Parent related
void	handle_redirections(t_token *token, int fd[2]);
void	helper_handle_redirect(char	*file_name, int fd, int flags);
void	wait_and_get_exit_status(t_shell *mshell);
void	cleanup_and_wait(t_shell *mshell);

#endif