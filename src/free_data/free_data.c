#include "../../includes/minishell.h"

/**
 * @brief Free allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure containing
 * 				allocated resources
 * @param token Double pointer to the token list to be freed
 */
void	handle_error_shell(t_shell *mshell, t_token **token)
{
	free_list(token);
	free_envp_list(mshell->env_list);
//	free_envp(mshell->env_var);
	free(mshell->fake_cwd);
	free(mshell->rd_l);
}

/**
 * @brief Free allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure containing
 * 				allocated resources
 * @param token Double pointer to the token list to be freed
 */
void	free_all(t_shell *mshell, t_token **token)
{
	free_envp_list(mshell->env_list);
	free_list(token);
//	free_envp(mshell->env_var);
	free(mshell->fake_cwd);
	free(mshell->rd_l);
}

/**
 * @brief Frees a linked list of tokens and all associated memory.
 * 
 * @param token Double pointer to the head of the token linked list.
 *              Can be NULL or point to NULL without causing errors.
 *              After execution, *token will be set to NULL.
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
				free((*token)->name);
				free(*token);
				*token = temp;
			}
			*token = NULL;
		}
	}
}

/**
 * @brief Frees a null-terminated array of strings (environment variables)
 * 
 * @param arr Pointer to a null-terminated array of strings to be freed
 * 
 * @note The array must be null-terminated for proper iteration
 * @note After calling this function, the pointer becomes invalid
 */
/*
void	free_envp(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}
*/

void	free_envp_content(char *name, char *content)
{
	free(name);
	name = NULL;
	free(content);
	content = NULL;
}

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
