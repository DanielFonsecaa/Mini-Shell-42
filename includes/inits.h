#ifndef INITS_H
# define INITS_H

//inits
void	init_shell_envp_cwd(t_shell *mshell);
int		init_shell_data(t_shell *mshell, t_token **token);
void	init_token_data(t_shell *mshell, t_token **token);
void	init_pipeline(t_shell *mshell);

//Command Utils
t_cmd	**set_cmd_arr(t_shell *mshell, t_token **token);
void	add_flag_arg_to_cmd(t_token **token, t_cmd *command);
int		count_type_till_pipe(t_token *token, int type);
int		count_num_commands(t_token **token);

//Envp Utils
char	**ft_copy_envp(t_envp *head);

// Pipe and Redirects Utils
void	pipe_and_redirects_count(t_shell *mshell, t_token **token);
void	create_pipes(int num_pipes, t_shell *mshell);

#endif
