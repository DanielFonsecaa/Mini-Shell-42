#ifndef EXECUTE_H
# define EXECUTE_H

void	execute_built_in(t_shell *mshell, t_token **token);
void	execute(t_shell *mshell, t_token **token);

//Utils
void    count_num_commands(t_shell *mshell, t_token **token);
char	*ft_get_path(char **envp, char *cmd);
void	execute_final(char *command, char **envp);
void	execute_pipeline(t_shell *mshell, t_token **token);

#endif
