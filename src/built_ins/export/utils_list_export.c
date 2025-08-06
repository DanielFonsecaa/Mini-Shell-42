#include "../../../includes/minishell.h"

/**
 * @brief Creates a new environment variable node.
 * 
 * @param name The name of the environment variable.
 * @param content The content of the environment variable.
 * @return t_envp* Pointer to the newly created node.
 */
t_envp	*create_node(char *name, char *content)
{
	t_envp	*node;

	node = safe_calloc(1, sizeof(t_envp));
	if (name[0] == '_' || ft_isalpha(*name))
	{
		node->name = ft_strdup(name);
		node->content = ft_strdup(content);
		node->exported = true;
	}
	node->next = NULL;
	return (node);
}
/**
 * @brief Adds a new node to the end of the environment variable list.
 * 
 * @param node Pointer to the head of the environment variable list.
 * @param new_node Pointer to the new node to be added.
 */
void	envp_list_addback(t_envp **node, t_envp *new_node)
{
	t_envp	*last;

	if (*node)
	{
		last = envp_get_last(*node);
		last->next = new_node;
	}
	else
		*node = new_node;
}
/**
 * @brief Gets the last node in the environment variable list.
 * 
 * @param node Pointer to the head of the environment variable list.
 * @return t_envp* Pointer to the last node in the list.
 */
t_envp	*envp_get_last(t_envp *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
/**
 * @brief Creates an environment variable list from an array of strings.
 * 
 * @param env_list Pointer to the head of the environment variable list.
 * @param env Array of strings for environment variables.
 */
void	create_envp_list(t_envp **env_list, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*name;
	char	*content;

	i = -1;
	while (env[++i])
	{
		k = 0;
		j = 0;
		while (env[i][j] != '=')
			j++;
		name = ft_substr(env[i], k, j);
		k += j;
		j = 0;
		while (env[i][k + j])
			j++;
		content = ft_substr(env[i], k + 1, j);
		if (!content)
			content = "";
		envp_list_addback(env_list, create_node(name, content));
		free_envp_content(name, content);
	}
}
/**
 * @brief Counts the number of nodes in the environment list
 * 
 * @param node Pointer to the head of the environment variable list.
 * @return int The number of nodes in the list.
 */
int	envp_list_size(t_envp *node)
{
	int		i;
	t_envp	*temp;

	i = 0;
	temp = node;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
