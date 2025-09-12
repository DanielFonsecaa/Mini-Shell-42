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
		if (temp->type == HERE)
			mshell->num_heredoc++;
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
 * @brief Counts the number of tokens of a specific type until a PIPE
 *
 * @param token Pointer to the starting token in the linked list
 * @param type The token type to count (e.g., WORD, REDIRECT, etc.)
 * @return The number of tokens of the specified type found before a PIPE token
 *         or end of list
 */
int	count_type_till_pipe(t_token *token, int type)
{
	int		i;
	t_token	*temp;

	temp = token;
	i = 0;
	(void)type;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == ARG || temp->type == FLAG)
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
char	**ft_copy_envp(t_envp *head)
{
	int		i;
	int		size;
	char	**ret;
	t_envp	*temp;

	temp = head;
	size = 0;
	i = -1;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	ret = safe_calloc((size + 1), sizeof(char *));
	temp = head;
	while (++i < size && temp)
	{
		if (temp->exported)
			ret[i] = ft_strjoin_three(temp->name, "=", temp->content);
		if (!ret[i])
		{
			free_arr(ret);
			return (NULL);
		}
		temp = temp->next;
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
	int	i;
//falta lidar com erros caso falhe
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
