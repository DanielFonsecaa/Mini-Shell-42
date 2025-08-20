#include "../../includes/minishell.h"

/**
 * @brief Handles the echo built-in command for the minishell
 *
 * @param mshell Pointer to the shell structure containing shell state
 * @param token Double pointer to the token structure
 */
void	handle_echo(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_token	**args_arr;
	bool	flag;
	int		i;

	i = 0;
	temp = *token;
	flag = false;
	args_arr = get_args(&temp);
	if (handle_n(args_arr, &i) > 0)
		flag = true;
	print_echo(args_arr, flag, i);
	mshell->exit_code = 0;
	free(args_arr);
}

/**
 * @brief Handles the -n flag parsing for the echo built-in command
 *
 * @param token Array of token pointers containing command arguments
 * @param i Pointer to the index in the token array, updated by reference
 * @return Updated index position after processing all valid -n flags
 */
int	handle_n(t_token **token, int *i)
{
	int	count;

	count = *i - 1;
	while (token[++count])
	{
		if (valid_n(token[count]->name) == 0)
			return (*i);
		*i += 1;
	}
	return (*i);
}

/**
 * @brief Validates if a string is a valid -n flag for the echo command
 *
 * @param str The string to validate as a -n flag
 * @return int Returns 1 if the string is a valid -n flag, 0 otherwise
 */
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

/**
 * @brief Prints the arguments for the echo command with proper formatting
 *
 * @param arr Array of token pointers to be printed
 * @param flag Boolean flag indicating if newline should be suppressed
 * @param i Starting index in the array to begin printing from
 */
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

/**
 * @brief Extracts arguments and flags from a token linked list into an array.
 * 
 * @param token Double pointer to the first token in the linked list.
 * @return t_token** Array of pointers to tokens.
 */
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
		if (temp->type == ARG || temp->type == FLAG)
			i++;
		temp = temp->next;
	}
	args_arr = safe_calloc(i + 1, sizeof(t_token *));
	temp = *token;
	i = 0;
	while (temp)
	{
		if (temp->type == ARG || temp->type == FLAG)
			args_arr[i++] = temp;
		temp = temp->next;
	}
	return (args_arr);
}
