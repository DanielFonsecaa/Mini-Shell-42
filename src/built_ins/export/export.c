#include "../../../includes/minishell.h"

/**
 * @brief Handles the export command.
 * 
 * @param mshell Pointer to the shell structure.
 * @param token Pointer to the token list.
 */
void handle_export(t_shell *mshell, t_token **token, int fd)
{
	t_token	*temp;

	temp = (*token)->next;
	mshell->exit_code = 1;
	if (check_for_flags(mshell))
		return ;
	if (!temp)
		show_export(mshell, mshell->env_list, fd);
	else
	{
		while (temp && temp->type != PIPE)
		{
			update_export(mshell, &temp);
			temp = temp->next;
		}
	}
}

/**
 * @brief Displays the exported environment variables.
 * 
 * @param node Pointer to the head of the environment variable list.
 */
void show_export(t_shell *mshell, t_envp *node, int fd)
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
	if (!arr)
		return ;
	i = 0;
	while (temp)
	{
		arr[i++] = temp;
		temp = temp->next;
	}
	bubble_sort(arr, list_size);
	i = -1;
	while (++i < list_size)
		ft_printf_fd(fd, DEFINE_X, arr[i]->name, arr[i]->content);
	free(arr);
	mshell->exit_code = 0;
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
	mshell->exit_code = 0;
	existing_node = find_envp(mshell->env_list, name);
	if (existing_node)
		return (update_envp_var(temp->name, existing_node));
	else
	{
		if (!validade_export_name(name))
		{
			mshell->exit_code = 1;
			return ;
		}
		if (has_content(name))
			return (create_envp_var(mshell, &temp, true));
		create_envp_var(mshell, &temp, false);
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
	char	*new_content;
	int		i;
	int		j;

	i = 0;
	while (name[i] && (name[i] != '=' && name[i] != '+'))
		i++;
	if (name[i] == '+')
		return (append_envp_var(name, node));
	j = 0;
	while (name[i + j])
		j++;
	old = node->content;
	new = ft_substr(name, i + 1, j);
	if (has_quote(new))
		new_content = ft_strtrim_char(new, which_quote(new));
	else
		new_content = ft_strdup(new);
	node->content = new_content;
	node->exported = true;
	free(old);
	free(new);
}

void	append_envp_var(char *name, t_envp *node)
{
	char	*new;
	char	*old;
	char	*new_content;
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
	if (has_quote(new))
		new_content = ft_strtrim_char(new, which_quote(new));
	else
		new_content = ft_strdup(new);
	node->content = ft_strjoin(old, new_content);
	node->exported = true;
	free(old);
	free(new);
	free(new_content);
}
