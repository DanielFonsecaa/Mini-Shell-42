#include "../../includes/minishell.h"

/**
 * @brief Executes a child command in a forked process.
 *
 * @param mshell Pointer to the shell structure 
 * @param token Pointer to token array for error handling cleanup
 * @param command Pointer to command structure
 */
void	execute_child_command(t_shell *mshell, t_token **token, t_cmd *command)
{
	char	*path;
	char	**exec_command;

	format_cmd(mshell, command);
	path = ft_get_path(mshell->env_var, command->name);
	if (!path)
	{
		handle_error_shell(mshell, token);
		ft_printf_fd(2, "command not found\n");
		exit(127);
	}

	exec_command = mshell->exec_command;
	if (execve(path, exec_command, mshell->env_var) == -1)
	{
		if (path != command->name)
			free(path);
		handle_error_shell(mshell, token);
		perror("execve");
		exit(126);
	}
}

/**
 * Sets up input/output redirection for a child process in a pipeline.
 *
 * @param index     The index of the current command in the pipeline
 * @param num_cmds  The total number of commands in the pipeline
 * @param pipes     2D array of pipe file descriptors [index][read=0/write=1]
 * @param fd        Array containing input (fd[0]) and output (fd[1])
 */
void	setup_child(int index, int num_cmds, int **pipes, int *fd)
{
	if (index == 0)
	{
		if (fd && fd[0] > 2)
			dup2(fd[0], STDIN_FILENO);
	}
	else
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index == num_cmds - 1)
	{
		if (fd && fd[1] > 2)
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(pipes[index][1], STDOUT_FILENO);
	if (fd)
		close_fds(pipes, num_cmds, fd[0], fd[1]);
	else
		close_fds(pipes, num_cmds, -1, -1);
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
	while (command->flags && command->flags[i++])
		size++;
	i = 0;
	while (command->args && command->args[i++])
		size++;
	mshell->exec_command = safe_calloc(size + 1, sizeof(char *));
	size = 0;
	i = 0;
	if (command->name)
		mshell->exec_command[i++] = command->name;
	while (command->flags && command->flags[size])
		mshell->exec_command[i++] = command->flags[size++];
	size = 0;
	while (command->args && command->args[size])
		mshell->exec_command[i++] = command->args[size++];
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
<<<<<<< HEAD:src/execute/path.c

void execute_final(t_shell *mshell, t_token **token, t_cmd *command)
{
	char	*path;
	char	**exec_command;

	format_cmd(mshell, command);
	path = ft_get_path(mshell->env_var, command->name);
	if (!path)
	{
		handle_error_shell(mshell, token);
		ft_printf_fd(2, "command not found\n");
		exit(127);
	}

	exec_command = mshell->exec_command;
	if (execve(path, exec_command, mshell->env_var) == -1)
	{
		if (path != command->name)
			free(path);
		handle_error_shell(mshell, token);
		perror("execve");
		exit(126);
	}
}

void setup_child(int index, int num_cmds, int **pipes, int *fd)
{
	if (index == 0)
	{
		if (fd && fd[0] > 2)
			dup2(fd[0], STDIN_FILENO);
	}
	else
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index == num_cmds - 1)
	{
		if (fd && fd[1] > 2)
			dup2(fd[1], STDOUT_FILENO);
		else if (pipes[index])  // If no redirection but has pipe
			dup2(pipes[index][1], STDOUT_FILENO);
	}
	else
		dup2(pipes[index][1], STDOUT_FILENO);
	if (fd)
		close_fds(pipes, num_cmds, fd[0], fd[1]);
	else
		close_fds(pipes, num_cmds, -1, -1);
}

void	format_cmd(t_shell *mshell, t_cmd *command)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (command->name)
		size++;
	while (command->flags && command->flags[i++])
		size++;
	i = 0;
	while (command->args && command->args[i++])
		size++;
	mshell->exec_command = safe_calloc(size + 1, sizeof(char *));
	size = 0;
	i = 0;
	if (command->name)
		mshell->exec_command[i++] = command->name;
	while (command->flags && command->flags[size])
		mshell->exec_command[i++] = command->flags[size++];
	size = 0;
	while (command->args && command->args[size])
		mshell->exec_command[i++] = command->args[size++];
}

//falta lidar com erros caso falhe
void	create_pipes(int num_pipes, t_shell *mshell)
{
	int	i;

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

// falta lidar com erros no create pipes caso falhe
void	init_pipeline(t_shell *mshell)
{
	int num_pipes;

	num_pipes = mshell->num_commands + mshell->num_redirecs - 1;
	create_pipes(num_pipes, mshell);
	mshell->pids = safe_malloc(sizeof(pid_t) * mshell->num_commands);
	if (!mshell->pids)
	{
		// ft_printf_fd(); display error
		// mshell->exit_code = X; and return ;
	}
}

/*
void	ft_here(char **argv, int *fd)
{
	char	*limiter;
	char	*line;
	int		pipe_fd[2];

	limiter = argv[2];
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		    && (line[ft_strlen(limiter)] == '\n'
		        || line[ft_strlen(limiter) + 1] == '\0'))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	fd[0] = pipe_fd[0];
}
*/
=======
>>>>>>> 5f99259 (Feature: Organized files, renamed funcitons and files, created init function):src/execute/child.c
