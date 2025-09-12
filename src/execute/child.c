#include "../../includes/minishell.h"

/**
 * @brief Executes a child command in a forked process.
 *
 * @param mshell Pointer to the shell structure 
 * @param token Pointer to token array for error handling cleanup
 * @param command Pointer to command structure
 */
void	exec_child_cmd(t_shell *ms, t_token **toke, t_token **head, t_cmd *cmd)
{
	char	*path;

	format_cmd(ms, cmd);
	path = ft_get_path(ms->env_var, cmd->name);
	handle_child();
	if (is_built_in(toke))
	{
		execute_built_in(ms, toke, STDOUT_FILENO);
		handle_child_free(ms, head, path);
		exit (ms->exit_code);
	}
	if (!path)
	{
		handle_error_shell(ms, head);
		cleanup_pipes(ms->pipes, ms->num_commands - 1, ms);
		ms->pipes = NULL;
		free(ms->pids);
		ms->pids = NULL;
		ft_printf_fd(2, ERR_CMD);
		exit(NOT_FOUND);
	}
	execve(path, ms->exec_command, ms->env_var);
	if (path != cmd->name)
		free(path);
	handle_error_shell(ms, head);
	cleanup_pipes(ms->pipes, ms->num_commands - 1, ms);
	ms->pipes = NULL;
	perror("execve");
	exit(FOUND_NOT_EXEC);
}

/**
 * Sets up input/output redirection for a child process in a pipeline.
 *
 * @param index     The index of the current command in the pipeline
 * @param num_cmds  The total number of commands in the pipeline
 * @param pipes     2D array of pipe file descriptors [index][read=0/write=1]
 * @param fd        Array containing input (fd[0]) and output (fd[1])
 */
void	setup_child(t_shell *mshell, int index, int *fd)
{
	if (mshell->heredoc_fd != NULL && mshell->num_heredoc > 0)
	{
		if (index < mshell->num_heredoc && mshell->heredoc_fd[index] >= 0)
		{
			dup2(mshell->heredoc_fd[index], STDIN_FILENO);
			close(mshell->heredoc_fd[index]);
		}
	}
	else if (index == 0)
	{
		if (fd && fd[0] > 2)
			dup2(fd[0], STDIN_FILENO);
	}
	else
		dup2(mshell->pipes[index - 1][0], STDIN_FILENO);
	if (index == mshell->num_commands - 1)
	{
		if (fd && fd[1] > 2)
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(mshell->pipes[index][1], STDOUT_FILENO);
	if (fd)
		close_fds(mshell->pipes, mshell->num_commands, fd[0], fd[1]);
	else
		close_fds(mshell->pipes, mshell->num_commands, -1, -1);
}

/**
 * @brief Formats a command structure into an executable command array.
 *
 * @param mshell Pointer to the shell structure
 * @param command Pointer to the command structure
 */
void	format_cmd(t_shell *mshell, t_cmd *command)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (command->name)
		size++;
	i = 0;
	while (command->args && command->args[i++])
		size++;
	mshell->exec_command = safe_calloc(size + 1, sizeof(char *));
	size = 0;
	i = 0;
	if (command->name)
		mshell->exec_command[i++] = ft_strdup(command->name);
	while (command->args && command->args[size])
		mshell->exec_command[i++] = ft_strdup(command->args[size++]);
}

/**
 * @brief Search for the full path of a command
 *
 * @param envp Array of environment variables
 * @param cmd The command name to search for
 * @return Returns the full path to the executable if found or NULL
 */
char	*ft_get_path(char **envp, char *cmd)
{
	char	**full_path;
	char	*half_path;
	char	*path;
	int		i;

	i = 0;
	if (!envp || !cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		half_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, F_OK | X_OK) == 0)
			return (free_arr(full_path), path);
		free(path);
		i++;
	}
	return (free_arr(full_path), NULL);
}
