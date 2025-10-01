#include "../../../includes/minishell.h"

/**
 * @brief Handles the export command.
 * 
 * @param mshell Pointer to the shell structure.
 * @param token Pointer to the token list.
 * @param fd
 */
void	handle_export(t_shell *mshell, t_token **token, int fd)
{
	t_token	*temp;
	int		flag;

	temp = (*token)->next;
	mshell->exit_code = 1;
	flag = 0;
	if (check_for_flags(mshell))
		return ;
	if (!temp || temp->type == PIPE)
		show_export(mshell, mshell->env_list, fd);
	else
	{
		while (temp && temp->type != PIPE)
		{
			update_export(mshell, &temp, &flag);
			temp = temp->next;
		}
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
	if (!name[i])
		return ;
	if (name[i] == '+')
		return (append_envp_var(name, node));
	j = 0;
	while (name[i + j])
		j++;
	old = node->content;
	new = ft_substr(name, i + 1, j);
	if (has_quote(new))
		new_content = skip_quotes(new);
	else
		new_content = ft_strdup(new);
	node->content = new_content;
	node->exported = true;
	free_strs(old, new);
}

char	*skip_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			j++;
		i++;
	}
	new_str = safe_malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
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
