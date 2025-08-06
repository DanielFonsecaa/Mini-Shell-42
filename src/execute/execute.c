#include "../../includes/minishell.h"

/**
 * @brief Executes built-in shell commands
 * 
 * @param mshell Pointer to the shell structure containing shell
 * 				state and environment
 * @param token Double pointer to the token structure containing
 * 				the command to execute
 * @return int Returns 1 if a built-in command was recognized and executed,
 *             0 if the command is not a built-in command
 */
void	execute_built_in(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		return ;
	else if (ft_strcmp(temp->name, "env") == 0)
		handle_env(mshell);
	else if (ft_strcmp(temp->name, "pwd") == 0)
		handle_pwd(mshell, token);
	else if (ft_strcmp(temp->name, "exit") == 0)
		handle_exit(mshell, token);
	else if (ft_strcmp(temp->name, "cd") == 0)
		return ;
	else if (ft_strcmp(temp->name, "export") == 0)
		return ;
	else if (ft_strcmp(temp->name, "unset") == 0)
		return ;
}

void	execute(t_shell *mshell, t_token **token)
{
	(void)mshell;
	if (is_built_in(token))
		execute_built_in(mshell, token);
	else
		ft_printf_fd(1, (*token)->name);
}
