#include "../../includes/minishell.h"

/**
 * @brief Executes a pipeline of commands
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to token array used for command execution
 */
void execute_pipe_redirect(t_shell *mshell, t_token **token)
{
	int		i;
	t_token	*temp;

	i = -1;
	temp = *token;
	while (++i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			return (perror("fork"));
		if (mshell->pids[i] == 0)
		{
			signal(SIGINT, handle_ctrl_c_child);
			handle_redirections(temp, mshell->fd);
			setup_child(i, mshell->num_commands, mshell->pipes, mshell->fd);
			execute_child_command(mshell, &temp, token, mshell->command[i]);
		}
		if (i > 0)
			close(mshell->pipes[i - 1][0]);
		if (i < mshell->num_commands - 1)
			close(mshell->pipes[i][1]);
		while (temp && temp->type != PIPE) {
			temp = temp->next;
		}
		if (temp) {
			temp = temp->next;
		}
	}
	cleanup_and_wait(mshell);
}

/**
 * @brief Handles input/output redirections for shell commands
 *
 * @param token Pointer to the first token in the token list to process
 * @param fd Array of file descriptors [0] for input, [1] for output
 */

void	handle_redirections(t_token *token, int fd[2])
{
	int	flags;

	(void)fd;
	while (token && token->type != PIPE)
	{
		if (token->type == INFILE)
		{
			flags = O_RDONLY;
			helper_handle_redirect(token->next->name, STDIN_FILENO, flags);
		}
		else if (token->type == OUTFILE)
		{
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			helper_handle_redirect(token->next->name, STDOUT_FILENO, flags);
		}
		else if (token->type == APPEND)
		{
			flags = O_WRONLY | O_CREAT | O_APPEND;
			helper_handle_redirect(token->next->name, STDOUT_FILENO, flags);
		}
		token = token->next;
	}
}

void	helper_handle_redirect(char	*file_name, int fd, int flags)
{
	int new_fd;

	new_fd = open(file_name, flags, 0644);
	if (new_fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(new_fd, fd);
	close(new_fd);
}

/**
 * @brief Waits for all child to complete and retrieves the exit status
 *        of the last command in the pipeline.
 *
 * @param mshell Pointer to the shell structure
 */
void	wait_and_get_exit_status(t_shell *mshell)
{
	int	i;
	int	status;

	i = 0;
	while (i < mshell->num_commands)
	{
		waitpid(mshell->pids[i], &status, 0);
		if (i == mshell->num_commands - 1)
		{
			if (WIFEXITED(status))
				mshell->exit_code = WEXITSTATUS(status);
			else
				mshell->exit_code = 1;
		}
		i++;
	}
}

/**
 * @brief Cleans up resources and waits for child processes to complete
 *
 * @param mshell Pointer to the shell structure
 */
void	cleanup_and_wait(t_shell *mshell)
{
	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
}
