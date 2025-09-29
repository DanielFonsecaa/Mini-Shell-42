#include "../../includes/minishell.h"

void	free_heredoc(t_shell *mshell)
{
	if (mshell->heredoc_fd)
	{
		free(mshell->heredoc_fd);
		mshell->heredoc_fd = NULL;
	}
}

/**
 * @brief Frees the content of an environment variable.
 * 
 * @param name The name of the environment variable.
 * @param content The content of the environment variable.
 */
void	free_strs(char *name, char *content)
{
	free(name);
	name = NULL;
	free(content);
	content = NULL;
}

/**
 * @brief Closes all file descriptors associated with a pipeline
 *
 * @param pipes Array of pipe file descriptor pairs to be closed
 * @param num_pipes Total number of pipes in the pipeline
 * @param fd_in Input file descriptor to close (if > 2)
 * @param fd_out Output file descriptor to close (if > 2)
 */
void	close_fds(int **pipes, int num_pipes, int *fd)
{
	int	i;

	i = 0;
	if (fd)
	{
		while (i < num_pipes - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
		if (fd[0] > 2)
			close(fd[0]);
		if (fd[1] > 2)
			close(fd[1]);
	}
	else
	{
		while (i < num_pipes - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
	}
}

/**
 * @brief Cleans up pipe resources and process IDs after pipeline execution
 *
 * @param pipes Array of pipe file descriptor pairs to be cleaned up
 * @param num_pipes Number of pipes in the pipes array
 * @param mshell Pointer to the shell structure containing process IDs to free
 */
void	cleanup_pipes(int **pipes, int num_pipes, t_shell *mshell)
{
	int	i;

	i = 0;
	(void)mshell;
	if (!pipes)
		return ;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
