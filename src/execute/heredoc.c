#include "../../includes/minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		ft_printf_fd(1, "\n");
		close(STDIN_FILENO);
		signal(SIGINT, heredoc_sigint_handler);
	}
}

int	create_heredoc(t_shell *mshell, char *limiter, t_token **head)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child_process(mshell, fd, limiter, head);
	else
	{
		close(fd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, heredoc_sigint_handler);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				close(fd[0]);
				handle_error_shell(mshell, head);
				g_sig = 130;
				mshell->exit_code = 130;
				return (-1);
			}
		}
		return (fd[0]);
	}
	return (-1);
}

void	heredoc_child_process(t_shell *mshell, int fd[2], char *limiter, t_token **head)
{
	char	*line;

	(void)head;
	close(fd[0]);
	signal(SIGINT, heredoc_sigint_handler);
	while (1 && g_sig != 130)
	{
		if (g_sig == 130)
		{
			heredoc_child_cleanup(mshell, head);
			if (mshell->heredoc_fd)
				free_heredoc(mshell);
			exit(130);
		}
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write_to_fd(mshell, fd[1], line);
		free(line);
	}
	heredoc_child_cleanup(mshell, head);
	if (mshell->heredoc_fd)
		free_heredoc(mshell);
	close(fd[1]);
	exit(0);
}

int	init_heredoc(t_shell *mshell, t_token **token, t_token **head)
{
	int		heredoc_count;
	int		i;
	int		pid;
	t_token	*temp;
	int		fd[2];
	int		status;
	char	*line;

	temp = *token;
	status = 0;
	block_parent_signals();
	heredoc_count = mshell->num_heredoc;
	if (heredoc_count == 0)
	{
		mshell->heredoc_fd = NULL;
		return (1);
	}
	
	// Initialize the array in parent process
	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	
	// Initialize all values to -1 (invalid fd)
	for (int j = 0; j < heredoc_count; j++)
		mshell->heredoc_fd[j] = -1;
	
	i = 0;
	// Create pipes BEFORE forking so both processes can access them
	while (temp && i < heredoc_count)
	{
		if (temp->type == HERE && temp->next)
		{
			if (pipe(fd) == -1)
				return (0);
			
			pid = fork();
			if (pid == -1)
				return (0);
			
			if (pid == 0)  // Child process
			{
				signal(SIGINT, handle_heredoc_signal);
				close(fd[0]);  // Child only writes, close read end
				
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, temp->next->name) == 0)
					{
						if (line)
							free(line);
						break;
					}
					write_to_fd(mshell, fd[1], line);
					if (line)
						free(line);
				}
				close(fd[1]);
				exit(0);
			}
			else  // Parent process
			{
				close(fd[1]);  // Parent only reads, close write end
				mshell->heredoc_fd[i] = fd[0];  // Store read end
				
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					close(fd[0]);
					handle_error_shell(mshell, token);
					g_sig = 130;
					mshell->exit_code = 130;
					return (0);
				}
				i++;
			}
		}
		temp = temp->next;
	}
	
	restore_parent_signals();
	return (1);
}

void	write_to_fd(t_shell *mshell, int fd, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			find_node_write_replace(mshell, fd, line, &i);
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
	while (line[*i] && line[*i] != ' ')
	{
		*i += 1;
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
}
