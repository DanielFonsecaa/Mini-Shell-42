#include "../../includes/minishell.h"

void	init_limiter(t_token *temp, char **limiter)
{
	*limiter = temp->next->name;
	if (*limiter[0] == '\'' || *limiter[0] == '"')
		*limiter = ft_strtrim_char(*limiter, which_quote(*limiter));
	else
		*limiter = ft_strdup(temp->next->name);
}

int	process_heredoc_line(t_shell *mshell, int fd, char *line, char *limiter)
{
	if (g_sig == 130)
	{
		if (line)
			free(line);
		return (1);
	}
	if (!line || ft_strcmp(line, limiter) == 0)
	{
		if (line)
			free(line);
		return (1);
	}
	write_to_fd(mshell, fd, line);
	if (line)
		free(line);
	return (0);
}

int	handle_heredoc(t_shell *mshell, char *limiter, int *fd, int i)
{
	char	*line;

	if (pipe(fd) == -1)
		exit(1);
	while (g_sig != 130)
	{
		line = readline("> ");
		if (process_heredoc_line(mshell, fd[1], line, limiter))
			break ;
	}
	close(fd[1]);
	if (g_sig == 130)
	{
		close(fd[0]);
		return (0);
	}
	mshell->heredoc_fd[i] = fd[0];
	return (1);
}

void	make_heredoc(t_shell *mshell, t_token *temp, int heredoc_count)
{
	char	*limiter;
	int		fd[2];
	int		i;

	i = 0;
	while (temp && i < heredoc_count && g_sig != 130)
	{
		if (temp->type == HERE && temp->next)
		{
			init_limiter(temp, &limiter);
			if (!handle_heredoc(mshell, limiter, fd, i))
			{
				if (limiter && limiter != temp->next->name)
				{
					free(limiter);
				}
				break ;
			}
			if (limiter && limiter != temp->next->name)
				free(limiter);
			i++;
		}
		temp = temp->next;
	}
}

int	setup_heredoc_array(t_shell *mshell, int heredoc_count)
{
	int	j;

	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	j = 0;
	while (j < heredoc_count)
	{
		mshell->heredoc_fd[j] = -1;
		j++;
	}
	return (1);
}
