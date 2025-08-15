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
void    execute_pipe_redirect(t_shell *mshell, t_token **token);
void    handle_redirections(t_token *token, int fd[2]);
void    cleanup_and_wait(t_shell *mshell);

#endif
/*
if (mshell->has_pipes && mshell->has_redirect)
{
init_pipeline(mshell);
execute_pipes_redirecs(mshell, token);
}
else if (!mshell->has_redirect && mshell->has_pipes)
{
init_pipeline(mshell);
execute_pipeline(mshell, token);
}
else if (mshell->has_redirect && !mshell->has_pipes)
{
init_pipeline(mshell);
execute_redirecs(mshell, token);
}*/