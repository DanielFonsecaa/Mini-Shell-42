#include "../../includes/minishell.h"

void	handle_echo(t_shell *mshell, t_token **token)
{
	t_token *temp;
	t_token **args_arr;
	bool	flag;
	int		i;

	i = 0;
	temp = *token;
	flag = false;
	//get printable args
	args_arr = get_args(&temp);
	if (handle_n(args_arr, &i) > 0)
		flag = true;
	//print arguments
	print_echo(args_arr, flag, i);
	//deal with pipes, redirect so on
	mshell->exit_code = 0;
	free(args_arr);
}

int	handle_n(t_token **token, int *i)
{
	int	count;

	count = *i - 1;
	while (token[++count])
		*i += valid_n(token[count]->name);
	return (*i);
}

int	valid_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		return (str[i] == '\0');
	}
	return (0);
}

void	print_echo(t_token **arr, bool flag, int i)
{
	int		size;
	char	*name;

	size = 0;
	while (arr[size])
		size++;
	while (arr[i])
	{
		if (arr[i]->has_quote)
			name = ft_strtrim_char(arr[i]->name, which_quote(arr[i]->name));
		else
			name = arr[i]->name;
		ft_printf_fd(1, "%s", name);
		if (i < size - 1)
			ft_printf(" ");
		if (arr[i]->has_quote)
			free(name);
		name = NULL;
		i++;
	}
	if (!flag)
		ft_printf_fd(1, "\n");
}


t_token	**get_args(t_token **token)
{
	t_token	*temp;
	t_token	**args_arr;
	int		i;

	args_arr = NULL;
	temp = *token;
	i = 0;
	while (temp)
	{
		if (temp->type == ARG)
			i++;
		temp = temp->next;
	}
	args_arr = safe_calloc(i + 1, sizeof(t_token *));
	temp = *token;
	i = 0;
	while (temp)
	{
		if (temp->type == ARG)
			args_arr[i++] = temp;
		temp = temp->next;
	}
	return (args_arr);
}

char	which_quote(char *str)
{
	return (*str);
}