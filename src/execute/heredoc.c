#include "../../includes/minishell.h"

int	init_heredoc(t_shell *mshell, t_token **token)
{
	int		heredoc_count;
	int		i;
	//int		pid;
	t_token	*temp;
	int		fd[2];
	int		stdin;
	char	*line;
	int		code;
	char	*limiter;

	temp = *token;
	block_parent_signals();
	heredoc_count = mshell->num_heredoc;
	if (heredoc_count == 0)
	{
		mshell->heredoc_fd = NULL;
		return (1);
	}
	stdin = dup(STDIN_FILENO);
	limiter = temp->next->name;
	if (limiter[0] == '\'' || limiter[0] == '"')
	{
		limiter = ft_strtrim_char(limiter, which_quote(limiter));
	}
	mshell->heredoc_fd = safe_malloc(sizeof(int) * heredoc_count);
	if (!mshell->heredoc_fd)
		return (0);
	for (int j = 0; j < heredoc_count; j++)
		mshell->heredoc_fd[j] = -1;
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
				if (!line || ft_strcmp(line, limiter) == 0 || g_sig == 130)
				{
					if (line)
						free(line);
					if (limiter)
					{
						free(limiter);
						limiter = NULL;
					}
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
		if (g_sig == 130)
        	break;
		temp = temp->next;
	}
	//free_heredoc_child(mshell, token);
	//close(fd[0]);
		//if (mshell->heredoc_fd)
		//	free(mshell->heredoc_fd);
	if (g_sig == 130)
		code = 130;
	else
		code = 0; // success, or exit(130) if you detect Ctrl+C in child
	g_sig = code;
	mshell->exit_code = code;
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	if (limiter)
		free(limiter);
	limiter = NULL;
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
