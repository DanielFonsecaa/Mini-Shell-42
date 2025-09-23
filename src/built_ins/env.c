#include "../../includes/minishell.h"

/**
 * @brief Handles the 'env' command
 * 
 * @param mshell Pointer to the shell structure
 * @param fd
 */
void	handle_env(t_shell *mshell, int fd)
{
	t_envp	*node;

	if (!mshell)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, ERR_COMPUTER_ERROR);
		return ;
	}
	if (!mshell->env_list)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, ERR_NO_ENVP);
		return ;
	}
	if (check_for_args(mshell))
		return ;
	node = mshell->env_list;
	while (node)
	{
		if (node->exported)
			ft_printf_fd(fd, "%s=%s\n", node->name, node->content);
		node = node->next;
	}
	mshell->exit_code = 0;
}

int	check_for_args(t_shell *mshell)
{
	int	i;
	int	check;

	i = 0;
	while (mshell->command[i])
	{
		check = 0;
		if (mshell->command[i]->args)
		{
			ft_printf_fd(2, ERR_NO_ARG_ALLOWED);
			return (1);
		}
		i++;
	}
	return (0);
}
