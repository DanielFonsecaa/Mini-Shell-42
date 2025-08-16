#include "../../includes/minishell.h"

<<<<<<< HEAD:src/execute/regular.c
void    execute_pipe_redirect(t_shell *mshell, t_token **token)
{
	int i;
	t_token *temp;

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
			execute_final(mshell, token, mshell->command[i]);
			exit(127);
		}
		while (temp && temp->type != PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
		if (i > 0)
			close(mshell->pipes[i-1][1]);
	}
	cleanup_and_wait(mshell);
}

void handle_redirections(t_token *token, int fd[2])
{
	while (token && token->type != PIPE)
	{
		if (token->type == INFILE)  // <
		{
			fd[0] = open(token->next->name, O_RDONLY);
			if (fd[0] == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		else if (token->type == OUTFILE)  // >
		{
			fd[1] = open(token->next->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd[1] == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (token->type == APPEND)  // >>
		{
			fd[1] = open(token->next->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd[1] == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		token = token->next;
	}
}

=======
/**
 * @brief Executes a pipeline of commands
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to token array used for command execution
 */
>>>>>>> 5f99259 (Feature: Organized files, renamed funcitons and files, created init function):src/execute/parent.c
void	execute_pipeline(t_shell *mshell, t_token **token)
{
	int	i;
	int	*fd_to_pass;

	i = -1;
	while (++i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		signal(SIGINT, handle_ctrl_c_child);
		if (mshell->pids[i] == -1)
			return (perror("fork"));
		if (mshell->pids[i] == 0)
		{
			fd_to_pass = NULL;
			if (mshell->fd[0] > 2 || mshell->fd[1] > 2)
				fd_to_pass = mshell->fd;
			setup_child(i, mshell->num_commands, mshell->pipes, fd_to_pass);
			execute_child_command(mshell, token, mshell->command[i]);
			exit(127);
		}
		if (i > 0)
			close(mshell->pipes[i-1][1]);
	}
	if (mshell->num_commands > 1)
		close(mshell->pipes[mshell->num_commands-2][0]);
	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
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
<<<<<<< HEAD:src/execute/regular.c
}

void cleanup_and_wait(t_shell *mshell)
{
	if (mshell->num_commands > 1)
		close(mshell->pipes[mshell->num_commands-2][0]);
	wait_and_get_exit_status(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
}
=======
}
>>>>>>> 5f99259 (Feature: Organized files, renamed funcitons and files, created init function):src/execute/parent.c
