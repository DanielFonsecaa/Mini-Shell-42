#include "../../../includes/minishell.h"

/**
 * @brief Sorts an array of environment variables in alphabetical order
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
	while (i < list_size)
	{
		j = i + 1;
		while (j < list_size)
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

void	create_envp_var(t_shell *mshell, t_token **token, bool exported)
{
	int		end;
	int		start;
	t_token	*temp;
	char	*name;
	char	*content;
	
	temp = (*token)->next;
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

int	validade_export_name(char *name)
{
	int	i;

	if (!(name[0] == '_' || ft_isalpha(*name)))
		return (ft_printf_fd(2, "export: %s: not a valid identifier\n", name), 0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (ft_printf_fd(2 ,"export: `%s': not a valid identifier\n", name), 0);
		i++;
	}
	return (1);
}

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

t_envp	*find_envp(t_envp *env_list, char *name)
{
	t_envp	*current;

	if (!name)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
