#include "../../includes/minishell.h"

/**
 * @brief Executes a command, either built-in or external
 *
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_cmd_line(t_shell *mshell, t_token **token)
{

	if (is_built_in(token) && !mshell->has_pipes && !mshell->has_redirect)
	{
		format_cmd(mshell, mshell->command[0]);
		execute_built_in(mshell, token);
		//free_arr(mshell->exec_command);
	}
	else
		execute_with_pipes_or_redirect(mshell, token);
}

/**
 * @brief Executes commands with pipes or redirections
 *
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_with_pipes_or_redirect(t_shell *mshell, t_token **token)
{
	if (mshell->has_pipes || mshell->has_redirect)
	{
		init_pipeline(mshell);
		execute_pipe_redirect(mshell, token);
	}
	else
	{
		//talvez aqui tenha que mudar quando so tem um comando com redirects
		mshell->pids = safe_malloc(sizeof(pid_t));
		mshell->pids[0] = fork();
		signal(SIGINT, handle_ctrl_c_child);
		if (mshell->pids[0] == -1)
		{
			perror("fork");
			return ;
		}
		if (mshell->pids[0] == 0)
		{
			execute_child_command(mshell, token, mshell->command[0]);
			exit(127);
		}
		wait_and_get_exit_status(mshell);
		free(mshell->pids);
	}
}

/**
 * @brief Executes built-in shell commands
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_built_in(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		handle_echo(mshell);
	else if (ft_strcmp(temp->name, "env") == 0)
		handle_env(mshell);
	else if (ft_strcmp(temp->name, "pwd") == 0)
		handle_pwd(mshell, token);
	else if (ft_strcmp(temp->name, "exit") == 0)
		handle_exit(mshell, token);
	else if (ft_strcmp(temp->name, "cd") == 0)
		handle_cd(mshell, token);
	else if (ft_strcmp(temp->name, "export") == 0)
		handle_export(mshell, token);
	else if (ft_strcmp(temp->name, "unset") == 0)
		handle_unset(mshell, token);
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