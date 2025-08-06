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
	int	i;

	i = 0;
	if (!mshell)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "Error: Computer error"); 
		return ;
	}
	if (!mshell->env_var)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "Error: No environment variables");
		return ;
	}
	while (mshell->env_var[i])
	{
		ft_printf("%s\n", mshell->env_var[i]);
		i++;
	}
	mshell->exit_code = 0;
}
