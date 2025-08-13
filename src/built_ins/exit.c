#include "../../includes/minishell.h"

//-9223372036854775808
//9223372036854775807
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
	if (ft_strlen(value) > 20 || !value)
			return (0);
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}
/**
 * @brief Handles the exit command in the shell
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	handle_exit(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	long long		status;
	char			*value;

	temp = *token;
	status = 0;
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
		printf("%lld\n", status);
		printf("LONG MAX --- %lld\n", LLONG_MAX);
		printf("LONG MIN --- %lld\n", LLONG_MIN);
		if (status > LLONG_MAX || status < LLONG_MIN)
			return ;
		if (status < 0 || status > 255)
			status %= 256;
		mshell->exit_code = status;
	}
	ft_printf_fd(mshell->exit_code, "exit\n");
	mshell->is_running = false;
}
