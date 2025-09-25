#ifndef EXECUTE_H
# define EXECUTE_H

//Main execution
void	execute_built_in(t_shell *mshell, t_token **token, int fd);
void	exec_child_cmd(t_shell *ms, t_token **t, t_token **h, t_cmd *c);
void	execute_cmd_line(t_shell *mshell, t_token **token);
void	execute_with_pipes_or_redirect(t_shell *mshell, t_token **token);
void	execute_pipe_redirect(t_shell *mshell, t_token **token);

//Child related
void	format_cmd(t_shell *mshell, t_cmd *command);
char	*ft_get_path(char **envp, char *cmd);
void	setup_child(t_shell *mshell, int index, int *fd, t_token *token);

//Parent related
void	handle_redirections(t_shell *mshell, t_token **head, t_token *token);
void	helper_handle_redir(t_shell *mshell, t_token *token,
			t_token **head, t_ints ints);
int		open_file_and_dup(char	*file_name, int fd, int flag, t_shell *mshell);
void	wait_and_get_exit_status(t_shell *mshell);
void	set_exitcode_status(t_shell *mshell, int status);
void	cleanup_and_wait(t_shell *mshell);
t_token	*get_command(t_token *token, int index);

//heredoc
int		create_heredoc(t_shell *mshell, char *limiter);
int		init_heredoc(t_shell *mshell, t_token **token);
void	write_to_fd(t_shell *mshell, int fd, char *line);
void	find_node_write_replace(t_shell *mshell, int fd, char *line, int *i);

#endif