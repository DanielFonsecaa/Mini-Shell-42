#include "../../../includes/minishell.h"

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
