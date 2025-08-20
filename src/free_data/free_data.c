#include "../../includes/minishell.h"

/**
 * @brief Frees a linked list of tokens and all associated memory.
 * 
 * @param token Double pointer to the head of the token linked list.
 */
void	free_list(t_token **token)
{
	t_token	*temp;

	if (token)
	{
		if (*token)
		{
			while (*token)
			{
				temp = (*token)->next;
				if ((*token)->name && (*token)->name[0])
					free((*token)->name);
				free(*token);
				*token = temp;
			}
			*token = NULL;
		}
	}
}

/**
 * @brief Frees a null-terminated array of strings 
 * 
 * @param arr Pointer to a null-terminated array of strings to be freed
 */

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

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
void	free_envp_list(t_envp *node)
{
	t_envp	*temp;

	if (!node)
		return ;
	while (node)
	{
		temp = node->next;
		free(node->name);
		free(node->content);
		free(node);
		node = temp;
	}
	node = NULL;
}

/**
 * @brief Frees a allocated array of command structures and their contents
 *
 * @param commands A pointer to an array of t_cmd pointers to be freed.
 */
void	free_cmd_struct(t_cmd **commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		if (commands[i]->name)
		{
			free(commands[i]->name);
			commands[i]->name = NULL;
		}
		if (commands[i]->flags)
			free_arr(commands[i]->flags);
		if (commands[i]->args)
			free_arr(commands[i]->args);
		if (commands[i])
			free(commands[i]);
		i++;
	}
	free(commands);
}
