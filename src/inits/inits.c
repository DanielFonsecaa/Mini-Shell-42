#include "../../includes/minishell.h"

/**
 * @brief Creates a deep copy of an environment variables array
 * 
 * @param envp Array of environment variable strings to copy (NULL-terminated)
 * @return char** Pointer to the newly allocated copy of the environment array,
 *                or NULL if memory allocation fails
 */
char	**ft_copy_envp(char **envp)
{
	int		i;
	int		size;
	char	**ret;

	size = 0;
	i = 0;
	while (envp[size])
		size++;
	ret = safe_calloc((size + 1), sizeof(char *));
	while (i < size && envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		if (!ret[i])
		{
//			free_envp(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

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
	existing_node->content = str_level;
	free(old_level);
}
