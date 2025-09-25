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
	t_token	*temp;

	temp = *token;
	heredoc_count = mshell->num_heredoc;
	if (heredoc_count == 0)
	{
		mshell->heredoc_fd = NULL;
		return (1);
	}
	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	i = 0;
	while (temp && i < heredoc_count)
	{
		if (g_sig == 130)
		{
			while (--i >= 0)
				close(mshell->heredoc_fd[i]);
			free(mshell->heredoc_fd);
			mshell->heredoc_fd = NULL;
			return (0);
		}
		else if (temp->type == HERE && temp->next)
		{
			mshell->heredoc_fd[i] = create_heredoc(mshell, temp->next->name, head);
			if (mshell->heredoc_fd[i] == -1 || g_sig == 130)
			{
				while (--i >= 0)
					close(mshell->heredoc_fd[i]);
				free(mshell->heredoc_fd);
				mshell->heredoc_fd = NULL;
				return (0);
			}
			i++;
		}
		temp = temp->next;
	}
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
