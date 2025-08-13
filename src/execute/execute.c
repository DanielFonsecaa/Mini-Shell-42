#include "../../includes/minishell.h"

/**
 * @brief Executes a command, either built-in or external
 *
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute(t_shell *mshell, t_token **token)
{
	if (is_built_in(token))
		execute_built_in(mshell, token);
    else
		execute_pipeline(mshell, token);
	//	ft_printf_fd(1, (*token)->name);
}



/**
 * @brief Executes built-in shell commands
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 * @return int Returns 1 if a built-in was recognized and executed,
 *             0 if is not a built-in
 */
void	execute_built_in(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		handle_echo(mshell, token);
	else if (ft_strcmp(temp->name, "env") == 0)
		handle_env(mshell);
	else if (ft_strcmp(temp->name, "pwd") == 0)
		handle_pwd(mshell, token);
	else if (ft_strcmp(temp->name, "exit") == 0)
		handle_exit(mshell, token);
	else if (ft_strcmp(temp->name, "cd") == 0)
		handle_cd(mshell, token);
	else if (ft_strcmp(temp->name, "export") == 0)
		handle_export(mshell, token);
	else if (ft_strcmp(temp->name, "unset") == 0)
		handle_unset(mshell, token);
	else
		return ;
}