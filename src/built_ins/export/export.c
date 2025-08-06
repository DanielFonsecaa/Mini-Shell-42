#include "../../../includes/minishell.h"

/**
 * @brief Handles the export command.
 * 
 * @param mshell Pointer to the shell structure.
 * @param token Pointer to the token list.
 */
void	handle_export(t_shell *mshell, t_token **token)
{
		t_token	*temp;

		temp = *token;
		if (!temp->next)
			show_export(mshell->env_list);
		else
			update_export(mshell, token);

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

void	update_export(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_envp	*existing_node;
	char	*name;

	temp = (*token)->next;
	name = temp->name;
	existing_node = find_envp(mshell->env_list, name);
	if (existing_node)
	{
		update_envp_var(token, existing_node);
		return ;
	}
	else
	{
		if (!validade_export_name(name))
		{
			mshell->exit_code = 1;
			return ;
		}
		if (has_content(name))
			create_envp_var(mshell, token, true);
		create_envp_var(mshell, token, false);
		mshell->exit_code = 0;
	}
}

void	update_envp_var(t_token **token, t_envp *node)
{
	t_token	*temp;
	char	*new;
	char	*old;
	int		i;

	i = 0;
	temp = (*token)->next;
	while (temp->name[i] != '=')
		i++;
	new = ft_strdup(temp->name + i + 1);
	old = node->content;
	node->content = new;
	free(old);
}