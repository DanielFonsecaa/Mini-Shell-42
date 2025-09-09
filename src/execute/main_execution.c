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
		if (mshell->pids[0] == -1)
		{
			perror("fork");
			free(mshell->pids);
			mshell->pids = NULL;
			return ;
		}
		if (mshell->pids[0] == 0)
		{
			handle_redirections(mshell, *token, mshell->fd);
			execute_child_command(mshell, token, token, mshell->command[0]);
		}
		wait_and_get_exit_status(mshell);
		free(mshell->pids);
		mshell->pids = NULL;
	}
}

/**
 * @brief Executes built-in shell commands
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void execute_built_in(t_shell *mshell, t_token **token)
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

int	create_heredoc(t_shell *mshell, char *limiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line)
			add_history(line);
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			//free, signals and stuff
			break ;
		}
		write_to_fd(mshell, fd[1], line); //to do
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	init_heredoc(t_shell *mshell, t_token **token)
{
	int		heredoc_count;
	t_token	*temp;

	temp = *token;
	heredoc_count = mshell->num_heredoc;
	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return; // handle error

	int i = 0;
	while (temp && i < heredoc_count) {
		if (temp->type == HERE && temp->next)
		{
			mshell->heredoc_fd[i] = create_heredoc(mshell, temp->next->name);
			// Optionally associate with command: mshell->command[cmd_index]->heredoc_fd = mshell->heredoc_fd[i];
			i++;
		}
		temp = temp->next;
	}
}

void	write_to_fd(t_shell *mshell, int fd, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			//find node and replace with expansion
			find_node_write_replace(mshell, fd, line, &i); //to do
			//node = find_envp(mshell->env_list, );
		}
		else
		{
			write(fd, &line[i], 1);
			i++;
		}
	}
	write(fd, "\n", 1);
}

void	find_node_write_replace(t_shell *mshell, int fd, char *line, int *i)
{
	t_envp	*node;
	int		j;
	int		start;
	char	*name;

	j = 0;
	start = *i;
	while(line[*i] && !ft_iswhite_space(line[*i]))
	{
		i++;
		j++;
	}
	name = ft_substr(line, start, j);
	node = find_envp(mshell->env_list, name);
	if (!node)
		return ;
	j = -1;
	while (node->content[++j])
		write(fd, &node->content[j], 1);
	free(name);
	//maybe free node
}
