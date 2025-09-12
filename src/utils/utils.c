#include "../../includes/minishell.h"

/**
 * @brief Modifies the shell level environment variable by a specified value
 *
 * @param node Pointer to the environment variable linked list to search in
 * @param value Integer value to add to the current shell level
 */
void	modify_shell_level(t_envp *node, int value)
{
	t_envp	*existing_node;
	char	*str_level;
	char	*old_level;
	int		new_level;

	existing_node = find_envp(node, "SHLVL");
	if (!existing_node)
	{
		ft_printf_fd(2, ERR_SHLVLNOT_FOUND);
		return ;
	}
	old_level = existing_node->content;
	new_level = ft_atoi(old_level);
	if (new_level >= 999)
	{
		ft_printf("bash: warning: shell level (%d) too high, resetting to 1\n", new_level + 1);
		str_level = ft_itoa(1);
	}
	else
		str_level = ft_itoa(new_level + value);
	if (!str_level)
	{
		ft_printf_fd(2, ERR_MEMORY_SHLVL);
		return ;
	}
	existing_node->content = str_level;
	existing_node->exported = true;
	free(old_level);
}

int	check_for_flags(t_shell *mshell)
{
	int	i;
	int	check;

	i = 0;
	while (mshell->command[i])
	{
		check = 0;
		if (!mshell->command[i]->args || !mshell->command[i]->args[check])
			return (0);
		while (mshell->command[i]->args[check])
		{
			if (mshell->command[i]->args[check][0] == '-')
			{
				mshell->exit_code = 1;
				ft_printf_fd(2, ERR_NO_FLAG_ALLOWED);
				return (1);
			}
			check++;
		}
		i++;
	}
	return (0);
}

char	*extract_cmd_token(char *rd_l, int *i)
{
	int		start;
	int		in_quote;
	char	quote_char;
	int		len;

	init_values(&len, &start, &in_quote, i);
	quote_char = 0;
	while (rd_l[(*i)])
	{
		if (!in_quote && (rd_l[*i] == '\'' || rd_l[*i] == '"'))
		{
			in_quote = 1;
			quote_char = rd_l[*i];
		}
		else if (in_quote && rd_l[*i] == quote_char)
			in_quote = 0;
		else if (!in_quote && ft_iswhite_space(rd_l[*i]))
			break ;
		else
			len++;
		(*i)++;
	}
	return (get_cmd_token(rd_l, start, len, quote_char));
}

char	*get_cmd_token(char *rd_l, int start, int len, char quote_char)
{
	char	*name;
	int		i;
	int		in_quote;

	name = safe_calloc(len + 1, sizeof(char));
	in_quote = 0;
	i = 0;
	while (i < len)
	{
		if (!in_quote && (rd_l[start] == '\'' || rd_l[start] == '"'))
		{
			in_quote = 1;
			quote_char = rd_l[start];
			start++;
			continue ;
		}
		else if (in_quote && rd_l[start] == quote_char)
		{
			in_quote = 0;
			start++;
			continue ;
		}
		name[i++] = rd_l[start++];
	}
	return (name);
}

/**
 * @brief Determines which type of quote char is at the beginning of a string.
 *
 * @param str Pointer to the string to examine
 * @return char of the first character of the string
 */
char	which_quote(char *str)
{
	return (*str);
}
