#include "../../includes/minishell.h"

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
			if (line)
				free(line);
			break ;
		}
		write_to_fd(mshell, fd[1], line);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	init_heredoc(t_shell *mshell, t_token **token)
{
	int		heredoc_count;
	int		i;
	t_token	*temp;

	temp = *token;
	handle_signal();
	heredoc_count = mshell->num_heredoc;
	if (heredoc_count == 0)
	{
		mshell->heredoc_fd = NULL;
		return (0);
	}
	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	i = 0;
	while (temp && i < heredoc_count)
	{
		if (temp->type == HERE && temp->next)
		{
			mshell->heredoc_fd[i] = create_heredoc(mshell, temp->next->name);
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
