#include "../../includes/minishell.h"

/**
 * @brief Handles the 'env' built-in command by printing
 * 			all environment variables
 * 
 * @param mshell Pointer to the shell structure containing
 * 			environment variables
 */
void	handle_env(t_shell *mshell)
{
	t_envp	*node;

	if (!mshell)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "Error: Computer error"); 
		return ;
	}
	if (!mshell->env_list)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "Error: No environment variables");
		return ;
	}
	node = mshell->env_list;
	while (node)
	{
		if (node->exported)
			ft_printf("%s=%s\n", node->name, node->content);
		node = node->next;
	}
	mshell->exit_code = 0;
}
