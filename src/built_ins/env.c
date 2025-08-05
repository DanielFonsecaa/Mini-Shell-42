#include "../../includes/minishell.h"

int	handle_env(t_shell *mshell)
{
	int	i;

	i = 0;
	if (!mshell)
			return (ft_printf_fd(2, "Error: Computer error") , 1);
	if (!mshell->env_var)
			return (ft_printf_fd(2, "Error: No enviroment variables"), 1);
	while (mshell->env_var[i])
	{
		ft_printf("%s\n", mshell->env_var[i]);
		i++;
	}
	return (0);
}
