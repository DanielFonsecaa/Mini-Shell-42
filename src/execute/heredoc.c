#include "../../includes/minishell.h"

int	init_heredoc(t_shell *mshell, t_token **token)
{
	int		heredoc_count;
	int		i;
	int		pid;
	t_token	*temp;
	int		fd[2];
	int		status;
	char	*line;

	temp = *token;
	block_parent_signals();
	heredoc_count = mshell->num_heredoc;
	if (heredoc_count == 0)
	{
		mshell->heredoc_fd = NULL;
		return (1);
	}

	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	for (int j = 0; j < heredoc_count; j++)
		mshell->heredoc_fd[j] = -1;
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0) // CHILD: handles ALL heredocs
	{
		signal(SIGINT, handle_heredoc_signal);
		temp = *token;
		i = 0;
		while (temp && i < heredoc_count)
		{
			if (temp->type == HERE && temp->next)
			{
				if (pipe(fd) == -1)
					exit(1);
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, temp->next->name) == 0 || g_sig == 130)
					{
						if (line)
							free(line);
						temp = temp->next;
						break;
					}
					if (g_sig != 130)
						write_to_fd(mshell, fd[1], line);
					if (line)
						free(line);
				}
				close(fd[1]);
				mshell->heredoc_fd[i] = fd[0];
				i++;
			}
            // If Ctrl+C, abort ALL heredocs immediately
			if (g_sig == 130) {
            	break;
        }
			temp = temp->next;
		}
		free_heredoc_child(mshell, token);
		if (mshell->heredoc_fd)
			free(mshell->heredoc_fd);
		if (g_sig == 130)
			exit(130);
		else
			exit(0); // success, or exit(130) if you detect Ctrl+C in child
	}
	else // PARENT
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) // child killed by signal
		{
			int sig = WTERMSIG(status);
			for (i = 0; i < heredoc_count; i++)
			{
				if (mshell->heredoc_fd[i] != -1)
					close(mshell->heredoc_fd[i]);
			}
			g_sig = 128 + sig;
			mshell->exit_code = 128 + sig;
		}
		else if (WIFEXITED(status)) // child called exit()
		{
			int code = WEXITSTATUS(status);
			if (code == 130) // Ctrl+C in heredoc!
			{
				for (i = 0; i < heredoc_count; i++)
				{
					if (mshell->heredoc_fd[i] != -1)
						close(mshell->heredoc_fd[i]);
				}
				g_sig = code;
				mshell->exit_code = code;
			}
		}
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
