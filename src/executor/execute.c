#include "../../includes/minishell.h"

int	execute_built_in(t_shell *mshell, t_token **token)
{
	(void)mshell;
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "env") == 0)
		return (handle_env(mshell));
	else if (ft_strcmp(temp->name, "pwd") == 0)
		return (handle_pwd(token));
	else if (ft_strcmp(temp->name, "exit") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "cd") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "export") == 0)
		return (1);
	else if (ft_strcmp(temp->name, "unset") == 0)
		return (1);
	return (0);
}

void	execute(t_shell *mshell, t_token **token)
{
	(void)mshell;
	if (!is_built_in(token))
		ft_printf_fd(1, (*token)->name);
	else
		execute_built_in(mshell, token);
}
