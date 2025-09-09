#include "../../includes/minishell.h"

/**
 * @brief Frees a linked list of tokens and all associated memory.
 * 
 * @param token Double pointer to the head of the token linked list.
 */
void	free_list(t_token **token)
{
	t_token	*temp;

	if (!token || !(*token))
		return ;
	while (*token)
	{
		temp = (*token)->next;
		if ((*token)->name)
			free((*token)->name);
		free(*token);
		*token = temp;
	}
	*token = NULL;
}

/**
 * @brief Frees a null-terminated array of strings 
 * 
 * @param arr Pointer to a null-terminated array of strings to be freed
 */

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
	arr = NULL;
}

//NOT BEING USED
/**
 * @brief Frees the content of an environment variable.
 * 
 * @param name The name of the environment variable.
 * @param content The content of the environment variable.
 */
void	free_envp_content(char *name, char *content)
{
	free(name);
	name = NULL;
	free(content);
	content = NULL;
}

/**
 * @brief Frees the entire environment variable list.
 * 
 * @param node Pointer to the head of the environment variable list.
 */
void	free_envp_list(t_shell *mshell)
{
	t_envp	*temp;
	t_envp	*node;

	if (!mshell || !mshell->env_list)
		return ;
	node = mshell->env_list;
	while (node)
	{
		temp = node->next;
		if (node->name)
			free(node->name);
		if (node->content)
			free(node->content);
		free(node);
		node = temp;
	}
	mshell->env_list = NULL;
}

/**
 * @brief Frees a allocated array of command structures and their contents
 *
 * @param commands A pointer to an array of t_cmd pointers to be freed.
 */
void	free_cmd_struct(t_shell *mshell)
{
	int	i;

	if (!mshell || !mshell->command)
		return ;
	i = -1;
	while (mshell->command[++i])
	{
		if (mshell->command[i]->name)
		{
			free(mshell->command[i]->name);
			mshell->command[i]->name = NULL;
		}
/*		if (mshell->command[i]->flags)
		{
			free_arr(mshell->command[i]->flags);
			mshell->command[i]->flags = NULL;
		}*/
		if (mshell->command[i]->args)
		{
			free_arr(mshell->command[i]->args);
			mshell->command[i]->args = NULL;
		}
		free(mshell->command[i]);
		mshell->command[i] = NULL;
	}
	free(mshell->command);
	mshell->command = NULL;
}
