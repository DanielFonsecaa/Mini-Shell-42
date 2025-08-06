#include "../../includes/minishell.h"

int	verify_num(char *value)
{
	int	i;

	i = 0;
	if (ft_strlen(value) > 20 || !value)
			return (0);
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	long long		status;
	char			*value;

	temp = *token;
	status = 0;
	mshell->is_running = false;
	if (temp->next)
	{
		value = temp->next->name;
		if (!verify_num(value))
		{
				mshell->exit_code = 2;
				ft_printf_fd(2, "Error exit: %s : numeric argument required\n", value);
				return ;
		}
		status = ft_atoll(value);
		if (status < 0 || status > 255)
			status %= 256;
		mshell->exit_code = status;
	}
	ft_printf_fd(mshell->exit_code, "exit\n");
}
