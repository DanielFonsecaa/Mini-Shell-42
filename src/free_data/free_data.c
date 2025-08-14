#include "../../includes/minishell.h"

/**
 * @brief Free allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	handle_error_shell(t_shell *mshell, t_token **token)
{
	free_list(token);
	free_envp_list(mshell->env_list);
	free_cmd_struct(mshell);
	free_arr(mshell->env_var);
	free(mshell->exec_command); //////////////
	free(mshell->fake_cwd);
	free(mshell->rd_l);

}

/**
 * @brief Free allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	free_all(t_shell *mshell, t_token **token)
{
	free_list(token);
	free_cmd_struct(mshell);
//	free_envp_list(mshell->env_list);
	free_arr(mshell->env_var);
	free(mshell->exec_command); ////////////
	free(mshell->fake_cwd);
	free(mshell->rd_l);
}

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

void    free_cmd_struct(t_shell *mshell)
{
	int i;

	i = 0;
	if (mshell->command[i])
	{
		while (mshell->command[i])
		{
			free(mshell->command[i]->name);
			if (mshell->command[i]->flags)
				free_arr(mshell->command[i]->flags);
			if (mshell->command[i]->args)
				free_arr(mshell->command[i]->args);
			if (mshell->command[i])
				free(mshell->command[i]);
			i++;
		}
		free(mshell->command);
		mshell->command = NULL;
	}
}

void	close_fds(int **pipes, int num_pipes, int fd_in, int fd_out)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
}

void	cleanup_pipes(int **pipes, int num_pipes, t_shell *mshell)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(mshell->pids);
}