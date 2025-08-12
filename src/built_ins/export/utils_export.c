#include "../../../includes/minishell.h"

/**
 * @brief Sorts an array of environment variables
 * 
 * @param arr Pointer to the array of environment variables
 * @param list_size Size of the array
 */
void	bubble_sort(t_envp **arr, int list_size)
{
	int		i;
	int		j;
	t_envp	*temp;

	i = 0;
	while (i < list_size - 1)
	{
		j = i + 1;
		while (j < list_size - 1)
		{
			if (ft_strcmp(arr[i]->name, arr[j]->name) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Creates a new environment variable and add to the list
 * 
 * @param mshell Pointer to the shell structure
 * @param token Pointer to the token
 * @param exported Boolean flag whether the variable should be exported
 */
void	create_envp_var(t_shell *mshell, t_token **token, bool exported)
{
	int		end;
	int		start;
	t_token	*temp;
	char	*name;
	char	*content;
	
	temp = *token;
	end = 0;
	start = 0;
	while(temp->name[end] && temp->name[end] != '=')
		end++;
	name = ft_substr(temp->name, start, end);
	start += end;
	end = 0;
	while (temp->name[end + start])
		end++;
	content = ft_substr(temp->name, start + 1, end);
	if (!content)
		content = "";
	envp_list_addback(&(mshell->env_list), create_node(name, content, exported));
	free_envp_content(name, content);
}

/**
 * @brief Validates an environment variable name
 *
 * @param name The variable name string to validate
 * @return 1 if the name is valid, 0 if invalid
 */
int	validade_export_name(char *name)
{
	int	i;

	if (!(name[0] == '_' || ft_isalpha(*name)))
		return (ft_printf_fd(2, "minishell: export: %s: not a valid identifier\n", name), 0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (ft_printf_fd(2 ,"minishell: export: `%s': not a valid identifier\n", name), 0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if a variable string contains a value.
 *
 * @param name The variable assignment string to check
 * @return 1 if the string contains an '=', 0 if no '=' is found
 */
int	has_content(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (name[i] == '=')
		return (1);
	return (0);
}

/**
 * @brief Finds an environment variable node by name
 * 
 * @param env_list Pointer to the head of the environment variables list
 * @param name The name of the environment variable to search
 * @return Pointer to the t_envp node if found, NULL if not found
 */
t_envp	*find_envp(t_envp *env_list, char *name)
{
	t_envp	*current;
	int		i;

	if (!name)
		return (NULL);
	current = env_list;
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	name = ft_substr(name, 0, i);
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(name);
			return (current);
		}
		current = current->next;
	}
	free(name);
	return (NULL);
}
