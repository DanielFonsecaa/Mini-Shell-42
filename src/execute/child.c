#include "../../includes/minishell.h"
#include <string.h>   // for strchr, ft_strnstr
#include <unistd.h>   // for access, F_OK, X_OK
#include <sys/stat.h> // for struct stat, stat, S_ISDIR

/**
 * @brief Executes a child command in a forked process.
 *
 * @param mshell Pointer to the shell structure 
 * @param token Pointer to token array for error handling cleanup
 * @param command Pointer to command structure
 */

static void	handle_cmd_not_found(t_shell *ms, t_token **head)
{
	handle_error_shell(ms, head);
	cleanup_pipes(ms->pipes, ms->num_commands - 1, ms);
	ms->pipes = NULL;
	free(ms->pids);
	ms->pids = NULL;
	ft_printf_fd(2, ERR_CMD);
	exit(NOT_FOUND);
}

static void	handle_execve_error(t_shell *ms, t_token **head,
	t_cmd *cmd, char *path)
{
	struct stat	st;

	if ((errno == EACCES) && (stat(path, &st) == 0) && S_ISDIR(st.st_mode))
	{
		ft_printf_fd(2, ERR_IS_DIR);
		handle_error_shell(ms, head);
		exit(126);
	}
	else
	{
		ft_printf_fd(2, "%s: %s\n", cmd->name, strerror(errno));
		handle_error_shell(ms, head);
		if (errno == EACCES || errno == EISDIR)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(1);
	}
}

void	exec_child_cmd(t_shell *ms, t_token **toke, t_token **head, t_cmd *cmd)
{
	char	*path;

	if (!cmd->name)
	{
		handle_child_free(ms, head, NULL);
		exit(0);
	}
	format_cmd(ms, cmd);
	path = ft_get_path(ms->env_var, cmd->name);
	handle_child();
	if (is_built_in(toke))
	{
		execute_built_in(ms, toke, STDOUT_FILENO);
		handle_child_free(ms, head, path);
		exit(ms->exit_code);
	}
	if (!path)
		handle_cmd_not_found(ms, head);
	execve(path, ms->exec_command, ms->env_var);
	if (path != cmd->name)
		free(path);
	cleanup_pipes(ms->pipes, ms->num_commands - 1, ms);
	ms->pipes = NULL;
	handle_execve_error(ms, head, cmd, path);
}

/**
 * Sets up input/output redirection for a child process in a pipeline.
 *
 * @param index     The index of the current command in the pipeline
 * @param num_cmds  The total number of commands in the pipeline
 * @param pipes     2D array of pipe file descriptors [index][read=0/write=1]
 * @param fd        Array containing input (fd[0]) and output (fd[1])
 */
void	setup_child(t_shell *mshell, int index, int *fd, t_token *token)
{
	setup_child_input(mshell, index, fd, token);
	if (index == mshell->num_commands - 1)
	{
		if (fd && fd[1] > 2)
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(mshell->pipes[index][1], STDOUT_FILENO);
	close_fds(mshell->pipes, mshell->num_commands, fd);
}

char	*ft_get_path(char **envp, char *cmd)
{
	char	**full_path;
	char	*result;
	int		i;

	i = 0;
	if (!envp || !cmd)
		return (NULL);
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':');
	result = find_executable_in_path(full_path, cmd);
	if (result)
		return (free_arr(full_path), result);
	return (free_arr(full_path), NULL);
}
