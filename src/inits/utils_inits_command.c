#include "../../includes/minishell.h"
/**
 * @brief Adds a token's name to a command's string array (flags or args)
 *
 * @param token Pointer to the token containing the name to add
 * @param dest The destination (flags or args)
 */
void	add_flag_arg_to_cmd(t_token **token, t_cmd *command)
{
	int	i;
	int	number_params;
	int	type;

	if ((*token)->type == TFILE)
		return ;
	i = 0;
	if ((*token)->type == ARG || (*token)->type == FLAG)
	{
		if ((*token)->type == ARG)
			type = ARG;
		else
			type = FLAG;
		number_params = count_type_till_pipe(*token, type);
		if (!command->args)
			command->args = safe_calloc(number_params + 1, sizeof(char *));
		while (command->args[i])
			i++;
		command->args[i] = ft_strdup((*token)->name);
	}
}

t_token	*add_to_array(t_cmd **cmd, t_token **head, t_token *token, int *i)
{
	t_token	*cmd_token;

	cmd[*i] = safe_calloc(1, sizeof(t_cmd));
	cmd_token = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD && !cmd_token)
			cmd_token = token;
		token = token->next;
	}
	if (cmd_token)
		cmd[*i]->name = ft_strdup(cmd_token->name);
	else
		cmd[*i]->name = NULL;
	token = get_command(*head, *i);
	while (token && token->type != PIPE)
	{
		if (token->type == ARG || token->type == FLAG)
			add_flag_arg_to_cmd(&token, cmd[*i]);
		token = token->next;
	}
	if (token && token->type == PIPE)
		token = token->next;
	*i += 1;
	return (token);
}

/**
 * @brief Creates and initializes an array of command structures
 *
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the first token in the linked list
 * 
 * @return t_cmd** Returns array of pointers to command structures.
 */
t_cmd	**set_cmd_arr(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_cmd	**command;
	int		i;
	int		size_arr;

	size_arr = mshell->num_commands;
	i = 0;
	temp = *token;
	if (size_arr <= 0)
		return (NULL);
	command = safe_calloc(size_arr + 1, sizeof(t_cmd *));
	while (i < size_arr)
		temp = add_to_array(command, token, temp, &i);
	return (command);
}

/**
 * @brief Counts the number of command tokens in a linked list of tokens
 *
 * @param token Double pointer to the first token in the linked list
 * @return int The total number of command tokens found in the list
 */
int	count_num_commands(t_token **token)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = *token;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}
