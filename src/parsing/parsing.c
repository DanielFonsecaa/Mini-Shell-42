#include "../../includes/minishell.h"

//debug arr of cmd --- erase latetr
static void     print_cmd_arr(t_shell *mshell)
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
		return (ft_printf_fd(2, ERR_QUOTE), 0);
	if (!tokenize(mshell->rd_l, token))
		return (0);
	mshell->tokens_size = token_list_size(*token);
	set_t_type(token);
	type_file(token);
	print_list(token);
	pipe_count(mshell, token);
	if (!syntax_error(mshell, token))
		return (0);
	count_num_commands(mshell, token);
	mshell->command = set_cmd_arr(mshell, token);
	print_cmd_arr(mshell);
	//return (0); //debug process
	ft_printf_fd(1, "token size --%i\n num pipes --%i\n", mshell->tokens_size,
		mshell->num_pipes);
	return (1);
}

t_cmd    **set_cmd_arr(t_shell *mshell, t_token **token)
{
	t_token *temp;
	t_cmd   **command;
	int     i;
	int     size_arr;

	size_arr = mshell->num_commands;
	i = -1;
	temp = *token;
	command = safe_calloc(size_arr + 1, sizeof(t_cmd *));
	while (i < size_arr && temp)
	{
		if (temp->type == CMD)
		{
			i++;
			command[i] = safe_calloc(1, sizeof(t_cmd));
			command[i]->name = ft_strdup(temp->name);
		}
		else if (temp->type == FLAG)
		{
			if (!command[i]->flags)
				command[i]->flags = safe_calloc(count_type_till_pipe(temp, FLAG) + 1, sizeof(char *));
			add_flag_to_cmd(&temp, &command[i]);
		}
		else if (temp->type == ARG)
		{
			if (!command[i]->args)
				command[i]->args = safe_calloc(count_type_till_pipe(temp, ARG) + 1, sizeof(char *));
			add_arg_to_cmd(&temp, &command[i]);
		}
		temp = temp->next;
	}
	return (command);
}

void    add_flag_to_cmd(t_token **token, t_cmd **command)
{
	int i;

	i = 0;
	while ((*command)->flags[i])
		i++;
	(*command)->flags[i] = ft_strdup((*token)->name);
}


void    add_arg_to_cmd(t_token **token, t_cmd **command)
{
	int i;

	i = 0;
	while ((*command)->args[i])
		i++;
	(*command)->args[i] = ft_strdup((*token)->name);
}

int    count_type_till_pipe(t_token *token, int type)
{
	int     i;
	t_token *temp;

	temp = token;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == type)
			i++;
		temp = temp->next;
	}
	return (i);
}