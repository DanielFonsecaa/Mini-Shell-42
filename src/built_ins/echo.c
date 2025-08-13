#include "../../includes/minishell.h"

void	handle_echo(t_shell *mshell, t_token **token)
{
	t_token *temp;
	t_token **args_arr;
	int		i;

	temp = (*token)->next;
	//get printable args
	args_arr = get_args(&temp);
	//print arguments
	i = 0;
	while (args_arr[i])
		ft_printf_fd(1, "%s", args_arr[i++]->name);
	ft_printf_fd(1, "\n");
	//deal with pipes, redirect so on
	mshell->exit_code = 0;
}

t_token	**get_args(t_token **token)
{
	t_token	*temp;
	t_token	**args_arr;
	int		i;

	i = 0;
	args_arr = NULL;
	temp = *token;
	while (temp)
	{
		if (temp->type == ARG)
			i++;
		temp = temp->next;
	}
	args_arr = safe_calloc(i , sizeof(t_token *));
	temp = *token;
	while (temp)
	{
		if (temp->type == ARG)
			args_arr[i++] = temp;
		temp = temp->next;
	}
	return (args_arr);
}