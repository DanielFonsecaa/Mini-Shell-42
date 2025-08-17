#include "../../includes/minishell.h"

/**
 * @brief Modifies the shell level environment variable by a specified value
 *
 * @param node Pointer to the environment variable linked list to search in
 * @param value Integer value to add to the current shell level
 */
void	modify_shell_level(t_envp *node, int value)
{
	t_envp	*existing_node;
	char	*str_level;
	char	*old_level;
	int		new_level;

	existing_node = find_envp(node, "SHLVL");
	if (!existing_node)
	{
		ft_printf_fd(2, "shell level not found");
		return ;
	}
	old_level = existing_node->content;
	new_level = ft_atoi(old_level);
	str_level = ft_itoa(new_level + value);
	if (!str_level)
	{
		ft_printf_fd(2, "Memory allocation failed for new shell level");
		return ;
	}
	existing_node->content = str_level;
	free(old_level);
}