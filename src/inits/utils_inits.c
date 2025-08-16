#include "../../includes/minishell.h"


/**
 * @brief Counts the number of pipes and redirections
 *
 * @param mshell Pointer to the shell structure where count will be stored
 * @param token Pointer to pointer of the first token in the linked list
 */
void	pipe_and_redirects_count(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	mshell->num_pipes = 0;
	mshell->num_redirecs = 0;
	mshell->has_pipes = false;
	mshell->has_redirect = false;
	temp = *token;
	while (temp)
	{
		if (temp->type == PIPE)
			mshell->num_pipes++;
		if (temp->type == APPEND || temp->type == INFILE
			|| temp->type == OUTFILE || temp->type == HERE)
			mshell->num_redirecs++;
		temp = temp->next;
	}
	if (mshell->num_pipes > 0)
		mshell->has_pipes = true;
	if (mshell->num_redirecs > 0)
		mshell->has_redirect = true;
}

/**
 * @brief Creates and initializes an array of command structures
 *
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the first token in the linked list
 * 
 * @return t_cmd** Returns a array of pointers to command structures.
 */
t_cmd	**set_cmd_arr(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	t_cmd	**command;
	int		i;
	int		size_arr;

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

/**
 * @brief Adds a flag token to the command's flags array
 * 
 * @param token Pointer to the token containing the flag name to be added
 * @param command Pointer to the command structure where will be stored
 */
void    add_flag_to_cmd(t_token **token, t_cmd **command)
{
	int i;

	i = 0;
	while ((*command)->flags[i])
		i++;
	(*command)->flags[i] = ft_strdup((*token)->name);
}


/**
 * @brief Adds a token's name as an argument to a command structure
 *
 * @param token Pointer to pointer to the token containing the name to add
 * @param command Pointer to pointer to the command structure to modify
 */
void    add_arg_to_cmd(t_token **token, t_cmd **command)
{
	int i;

	i = 0;
	while ((*command)->args[i])
		i++;
	(*command)->args[i] = ft_strdup((*token)->name);
}

/**
 * @brief Counts the number of tokens of a specific type until a PIPE
 *
 * @param token Pointer to the starting token in the linked list
 * @param type The token type to count (e.g., WORD, REDIRECT, etc.)
 * @return The number of tokens of the specified type found before a PIPE token
 *         or end of list
 */
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

/**
 * @brief Counts the number of command tokens in a linked list of tokens
 *
 * @param token Double pointer to the first token in the linked list
 * @return int The total number of command tokens found in the list
 */
int count_num_commands(t_token** token)
{
	t_token *temp;
	int     i;

	i = 0;
	temp = *token;
	while (temp)
	{
		if (temp->type == CMD)
			i++;
		temp = temp->next;
	}
	return (i);
}

/**
 * @brief Creates a deep copy of an environment variables array
 *
 * @param envp Array of environment variable strings to copy (NULL-terminated)
 * @return char** Pointer to the newly allocated copy of the environment array,
 *                or NULL if memory allocation fails
 */
char	**ft_copy_envp(char **envp)
{
	int		i;
	int		size;
	char	**ret;

	size = 0;
	i = 0;
	while (envp[size])
		size++;
	ret = safe_calloc((size + 1), sizeof(char *));
	while (i < size && envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		if (!ret[i])
		{
			free_arr(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

/**
 * @brief Creates an array of pipes for communication
 *
 * @param num_pipes Number of pipes to create (must be > 0)
 * @param mshell Pointer to the shell structure where pipes will be stored
 */
void	create_pipes(int num_pipes, t_shell *mshell)
{
	//falta lidar com erros caso falhe
	int	i;

	i = 0;
	if (num_pipes <= 0)
		return ;
	mshell->pipes = safe_calloc(num_pipes, sizeof(int *));
	//if (!mshell->pipes)
	// mshell->exit_code = X; and return ;
	while (i < num_pipes)
	{
		mshell->pipes[i] = safe_calloc(2, sizeof(int));
		if (pipe(mshell->pipes[i]) == -1)
		{
			mshell->exit_code = 1;
			return ;
		}
		i++;
	}
}
