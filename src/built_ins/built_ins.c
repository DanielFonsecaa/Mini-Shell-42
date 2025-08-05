#include "../../includes/minishell.h"

int	is_built_in(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "env") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "exit") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "cd") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "export") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "unset") == 0)
		return (1);
	else
		return (0);
}
