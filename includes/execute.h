/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:38:15 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:38:16 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	setup_child_input(t_shell *mshell, int index,
			int *fd, t_token *token);
char	*ft_get_path(char **envp, char *cmd);
void	setup_child(t_shell *mshell, int index, int *fd, t_token *token);
int		command_has_heredoc(t_token *token, int target_index);
int		get_command_heredoc_fd(t_shell *mshell, t_token *token, int i);
char	*find_executable_in_path(char **full_path, char *cmd);

//Parent related
void	handle_redirections(t_shell *mshell, t_token **head, t_token *token);
void	helper_handle_redir(t_shell *mshell, t_token *token,
			t_token **head, t_ints ints);
int		open_file_and_dup(char	*file_name, int fd, int flag, t_shell *mshell);
void	wait_and_get_exit_status(t_shell *mshell);
void	set_exitcode_status(t_shell *mshell, int status);
void	cleanup_and_wait(t_shell *mshell);
t_token	*get_command(t_token *token, int index);
void	handle_single_command(t_shell *mshell, t_token **token, t_token *temp);

//heredoc
int		init_heredoc(t_shell *mshell, t_token **token);
int		handle_heredoc(t_shell *mshell, char *limiter, int *fd, int i);
int		process_heredoc_line(t_shell *mshell, int fd, char *line, char *lim);
int		setup_heredoc_array(t_shell *mshell, int heredoc_count);
void	write_to_fd(t_shell *mshell, int fd, char *line);
void	make_heredoc(t_shell *mshell, t_token *temp, int heredoc_count);
void	find_node_write_replace(t_shell *mshell, int fd, char *line, int *i);
void	init_limiter(t_token *temp, char **limiter);

#endif
