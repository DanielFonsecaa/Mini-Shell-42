#ifndef EXECUTE_H
# define EXECUTE_H

//Main execution
void	execute_built_in(t_shell *mshell, t_token **token);
void	execute_child_command(t_shell *mshell, t_token **token, t_cmd *command);
void	execute_cmd_line(t_shell *mshell, t_token **token);
void	execute_with_pipes_or_redirect(t_shell *mshell, t_token **token);
void	execute_pipeline(t_shell *mshell, t_token **token);

//Child related
void	format_cmd(t_shell *mshell, t_cmd *command);
char	*ft_get_path(char **envp, char *cmd);
void	setup_child(int index, int num_cmds, int **pipes, int *fd);
<<<<<<< HEAD
void	init_pipeline(t_shell *mshell);
void    pipes(t_shell *mshell, t_token **token);
void    execute_pipe_redirect(t_shell *mshell, t_token **token);
void    handle_redirections(t_token *token, int fd[2]);
void    cleanup_and_wait(t_shell *mshell);
=======

//Parent related
void    wait_and_get_exit_status(t_shell *mshell);
>>>>>>> 5f99259 (Feature: Organized files, renamed funcitons and files, created init function)

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