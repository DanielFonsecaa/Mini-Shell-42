#ifndef EXECUTE_H
# define EXECUTE_H

void	execute_built_in(t_shell *mshell, t_token **token);
void	execute(t_shell *mshell, t_token **token);

//Utils
void    count_num_commands(t_shell *mshell, t_token **token);
char	*ft_get_path(char **envp, char *cmd);
void    execute_final(t_shell *mshell, t_token **token, t_cmd *command);
void	execute_pipeline(t_shell *mshell, t_token **token);
void    format_cmd(t_shell *mshell, t_cmd *command);
void    wait_and_get_exit_status(t_shell *mshell);
void	setup_child(int index, int num_cmds, int **pipes, int *fd);
void	init_pipeline(t_shell *mshell);
void    pipes(t_shell *mshell, t_token **token);

#endif
