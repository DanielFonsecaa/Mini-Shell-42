#include "../../includes/minishell.h"

/**
 * @brief Closes all file descriptors associated with a pipeline
 *
 * @param pipes Array of pipe file descriptor pairs to be closed
 * @param num_pipes Total number of pipes in the pipeline
 * @param fd_in Input file descriptor to close (if > 2)
 * @param fd_out Output file descriptor to close (if > 2)
 */
void	close_fds(int **pipes, int num_pipes, int fd_in, int fd_out)
{
	int	i;

	i = 0;
	while (i < num_pipes - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
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
