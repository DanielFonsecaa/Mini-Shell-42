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
int	execute_built_in(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	(void)mshell;
	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "env") == 0)
		return (handle_env(mshell));
	else if (ft_strcmp(temp->name, "pwd") == 0)
		return (handle_pwd(token));
	else if (ft_strcmp(temp->name, "exit") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "cd") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "export") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "unset") == 0)
		return (1);
	return (0);
}

void	execute(t_shell *mshell, t_token **token)
{
	(void)mshell;
	if (!is_built_in(token))
		ft_printf_fd(1, (*token)->name);
	else
		execute_built_in(mshell, token);
}
