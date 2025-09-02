#include "../../includes/minishell.h"

/**
 * @brief Handles the exit command in the shell
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void handle_exit(t_shell *mshell, t_token **token, int fd)
{
	t_token		*temp;
	long long	status;
	char		*value;

	temp = *token;
	status = 0;
	mshell->is_running = false;
	ft_printf("exit handle - %d\n",mshell->exit_code);
	if (temp->next)
	{
		value = temp->next->name;
		if (!verify_num(value) || !ft_atoll(value, &status))
		{
			mshell->exit_code = 2;
			ft_printf_fd(fd, ERR_EXIT_NOT_NBR, value);
			return ;
		}
		if (status < 0 || status > 255)
			status %= 256;
		mshell->exit_code = status;
	}
	ft_printf_fd(fd, "exit\n");
}

/**
 * @brief Verifies if the given string is a valid number.
 * 
 * @param value The string to be checked.
 * @return int Returns 1 if is a valid number, 0 otherwise.
 */
int	verify_num(char *value)
{
	int	i;

	i = 0;
	if (ft_strlen(value) > 20 || !value || !*value)
		return (0);
	if (value[i] == '-' || value[i] == '+')
		i++;
	if (!value[i])
		return (0);
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}
