#include "../../includes/minishell.h"

t_envp	*create_node(char *name, char *content)
{
	t_envp	*node;

	node = safe_calloc(1, sizeof(t_envp));
	if (name[0] == '_' || ft_isalpha(*name))
	{
		node->name = ft_strdup(name);
		node->content = ft_strdup(content);
	}
	node->next = NULL;
	return (node);
}

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

t_envp	*envp_get_last(t_envp *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	create_envp_list(t_envp **env_list, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*name;
	char	*content;

	i = 0;
	while (env[i])
			i++;
	i = 0;
	while (env[i])
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
		envp_list_addback(env_list, create_node(name, content));
		i++;
		free_envp_content(name, content);
	}
}

void	free_envp_content(char *name, char *content)
{
	free(name);
	name = NULL;
	free(content);
	content = NULL;
}

void	free_envp_list(t_envp *node)
{
	t_envp	*temp;

	if (!node)
		return ;
	while (node)
	{
		temp = node->next;
		free(node->name);
		free(node->content);
		free(node);
		node = temp;
	}
	node = NULL;
}

void	print_list2(t_envp *node)
{
	t_envp *temp;

	temp = node;
	while (temp)
	{
		ft_printf_fd(1, "%s=%s\n", temp->name, temp->content);
		temp = temp->next;
	}
}
/*
void	handle_export(t_shell *shell, t_token **token)
{
	create_envp_list(mshell->env_list, mshell->env_var)
}*/
