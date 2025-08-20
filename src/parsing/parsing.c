#include "../../includes/minishell.h"

//debug arr of cmd --- erase latetr
static void	print_cmd_arr(t_shell *mshell)
{
	int i = -1;
	int j;
	while (mshell->command[++i])
	{
		ft_printf_fd(1, " name -> %s\n", mshell->command[i]->name);
		j = -1;
		if (mshell->command[i]->flags)
		{
			while (mshell->command[i]->flags[++j]) {
				ft_printf_fd(1, " flag %d -> %s\n", j, mshell->command[i]->flags[j]);
			}
		}
		j = -1;
		if (mshell->command[i]->args)
		{
			while (mshell->command[i]->args[++j]) {
				ft_printf_fd(1, " arg %d -> %s\n", j, mshell->command[i]->args[j]);
			}
		}
	}
}

/**
 * @brief Parses the command line input and processes tokens for the minishell
 * 
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to the token list that will be populated
 */
int	parsing(t_shell *mshell, t_token **token)
{
	if (!quote_checker(mshell->rd_l))
	{
		mshell->exit_code = 2;
		return (ft_printf_fd(2, ERR_QUOTE), 0);
	}
	if (!tokenize(mshell->rd_l, token))
	{
		mshell->exit_code = 2;
		return (0);
	}
	init_token_data(mshell, token);
	if (!init_shell_data(mshell, token))
	{
		mshell->exit_code = 2;
		return (0);
	}
	print_cmd_arr(mshell);
	return (1);
}

void	expansion(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	char	*new_str;
	int		i;

	temp = *token;
	while (temp)
	{
		i = 0;
		new_str = safe_calloc(ft_strlen(temp->name) + 1, sizeof(char));
		while (temp->name[i])
		{
			if (temp->name[i] == '$' && temp->name[i + 1] == '?' && temp->type == ARG)
				append_exit_code(mshell, new_str, &i);
			else if (temp->name[i] == '$' && temp->type == ARG)
				new_str = append_expansion_content(&temp, new_str, &i);
			else
				new_str = append_letter(&temp, new_str, &i);
		}
		free(temp->name);
		temp->name = ft_strdup(new_str);
		free(new_str);
		temp = temp->next;
	}
}

char	*append_exit_code(t_shell *mshell, char *new_str, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(mshell->exit_code);
	new_str = ft_strjoin_free(new_str, exit_code);
	free(exit_code);
	*i += 2;
	return (new_str);
}

char	*append_expansion_content(t_token **token, char *new_str, int *i)
{
	t_envp	*node;
	char	*variable;
	char	*new_content;
	int		start;
	int		len;

	start = i + 1;
	len = 0;
	while (temp->name[start + len])
	{
		if (!(ft_isalnum(temp->name[start + len]) || temp->name[start + len] == '_'))
			break ;
		len++;
	}
	variable = ft_substr(temp->name, start, len);
	node = find_envp(mshell->env_list, variable);
	if (node)
		new_content = node->content;
	else
		new_content = "";
	new_str = ft_strjoin_free(new_str, new_content);
	free(variable);
	*i = start + len;
	return (new_str);
}

char	*append_letter(t_token **token, char *old_str, int *i)
{
	char	tmp[2];

	tmp[0] = (*token)->name[i];
	tmp[1] = 0;
	new_str = ft_strjoin_free(old_str, tmp);
	(*i)++;
	return (new_str);
}
