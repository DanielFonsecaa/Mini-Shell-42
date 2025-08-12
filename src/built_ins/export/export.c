#include "../../../includes/minishell.h"

//remove later, just for debbug
static void	print_full_variables_of_list(t_envp *head)
{
	t_envp	*node;
	
	node = head;
	while(node)
	{
		ft_printf_fd(1, "name -> %s\n", node->name);
		ft_printf_fd(1, "content -> %s  %s\n", node->content ? "true" : "false", node->content);
		ft_printf_fd(1, "exported -> %s\n", node->exported ? "true" : "false");
		node = node->next;
	}
}

/**
 * @brief Handles the export command.
 * 
 * @param mshell Pointer to the shell structure.
 * @param token Pointer to the token list.
 */
void	handle_export(t_shell *mshell, t_token **token)
{
		t_token	*temp;

		temp = (*token)->next;
		if (!temp)
			show_export(mshell->env_list);
		else
			update_export(mshell, &temp);

}

/**
 * @brief Displays the exported environment variables.
 * 
 * @param node Pointer to the head of the environment variable list.
 */
void	show_export(t_envp *node)
{
	t_envp	**arr;
	t_envp	*temp;
	int		list_size;
	int		i;

	if (!node)
		return ;
	list_size = envp_list_size(node);
	temp = node;
	arr = safe_calloc(list_size + 1, sizeof(t_envp *));
	i = 0;
	while (temp)
	{
		arr[i++] = temp;
		temp = temp->next;
	}
	bubble_sort(arr, list_size);
	i = 0;
	while (i < list_size)
	{
		ft_printf_fd(1, "declare -x %s=\"%s\"\n", arr[i]->name, arr[i]->content);
		i++;
	}
	free(arr);
}

/**
 * @brief Updates or creates an environment variable
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Pointer to pointer of the current token
 */
void	update_export(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_envp	*existing_node;
	char	*name;

	temp = *token;
	name = temp->name;
	existing_node = find_envp(mshell->env_list, name);
	if (existing_node)
	{
		update_envp_var(temp->name, existing_node);
		return ;
	}
	else
	{
		if (!validade_export_name(name))
		{
			mshell->exit_code = 1;
			return ;
		}
		mshell->exit_code = 0;
		if (has_content(name))
		{
			create_envp_var(mshell, &temp, true);
			print_full_variables_of_list(mshell->env_list); //remove this shitty function latter
			return ;
		}
		create_envp_var(mshell, &temp, false);
		print_full_variables_of_list(mshell->env_list);  //remove this shitty function latter
	}
}

/**
 * @brief Updates an environment variable node
 * 
 * @param name The name=value string containing the new variable
 * @param node Pointer to the variable node to be updated
 */
void	update_envp_var(char *name, t_envp *node)
{
	char	*new;
	char	*old;
	int		i;
	int		j;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	j = 0;
	while (name[i + j])
		j++;
	new = ft_substr(name, i + 1, j);
	old = node->content;
	node->content = new;
	node->exported = true;
	free(old);
}
