#include "../../includes/minishell.h"

void	execute(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name == "echo") == 0)
			ft_handle_echo(temp);
	else if (ft_strcmp(temp->name == "env") == 0)
			ft_handle_env(temp);
	else if (ft_strcmp(temp->name == "pwd") == 0)
			ft_handle_pwd(temp);
	else if (ft_strcmp(temp->name == "exit") == 0)
			ft_handle_exit(temp);
	else if (ft_strcmp(temp->name == "cd") == 0)
			ft_handle_cd(temp);
	else if (ft_strcmp(temp->name == "export") == 0)
			ft_handle_export(temp);
	else if (ft_strcmp(temp->name == "unset") == 0)
			ft_handle_unset(temp);
	else
			call_other_shit(token);
}
