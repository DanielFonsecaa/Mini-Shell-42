#include "../../../includes/minishell.h"

static int	count_extra_backticks(const char *content)
{
	int	i;
	int	extra;

	i = 0;
	extra = 0;
	while (content[i])
	{
		if (content[i] == '`')
			extra++;
		i++;
	}
	return (extra);
}

static void	print_export_list(t_envp **arr, int list_size, int fd)
{
	int		i;
	char	*escaped;

	escaped = NULL;
	i = -1;
	while (++i < list_size)
	{
		escaped = escape_export_content(arr[i]->content);
		if (escaped)
		{
			ft_printf_fd(fd, DEFINE_X, arr[i]->name, escaped);
			free(escaped);
		}
		else
			ft_printf_fd(fd, DEFINE_X, arr[i]->name, "");
	}
}

/**
 * @brief Displays the exported environment variables.
 * 
 * @param node Pointer to the head of the environment variable list.
 * @param fd
 */
void	show_export(t_shell *mshell, t_envp *node, int fd)
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
	print_export_list(arr, list_size, fd);
	free(arr);
	mshell->exit_code = 0;
}

char	*escape_export_content(const char *content)
{
	int		i;
	int		j;
	int		extra;
	char	*escaped;

	if (!content)
		return (NULL);
	extra = count_extra_backticks(content);
	i = 0;
	j = 0;
	while (content[i])
		i++;
	escaped = safe_malloc(i + extra + 1);
	if (!escaped)
		return (NULL);
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '`')
			escaped[j++] = '\\';
		escaped[j++] = content[i++];
	}
	escaped[j] = '\0';
	return (escaped);
}

/**
 * @brief Updates or creates an environment variable
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Pointer to pointer of the current token
 */
void	update_export(t_shell *mshell, t_token **token, int *flag)
{
	t_token	*temp;
	t_envp	*existing_node;
	char	*name;

	temp = *token;
	name = temp->name;
	if (!(*flag))
		mshell->exit_code = 0;
	existing_node = find_envp(mshell->env_list, name);
	if (existing_node)
		return (update_envp_var(temp->name, existing_node));
	else
	{
		if (!validade_export_name(name))
		{
			mshell->exit_code = 1;
			*flag = 1;
			return ;
		}
		if (has_content(name))
			return (create_envp_var(mshell, &temp, true));
		create_envp_var(mshell, &temp, false);
	}
}
