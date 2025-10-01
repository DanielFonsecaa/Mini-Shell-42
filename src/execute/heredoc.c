#include "../../includes/minishell.h"

int	init_heredoc(t_shell *mshell, t_token **token)
{
	t_token	*temp;
	int		stdin;

	temp = *token;
	block_parent_signals();
	if (mshell->num_heredoc == 0)
	{
		mshell->heredoc_fd = NULL;
		return (1);
	}
	stdin = dup(STDIN_FILENO);
	if (!setup_heredoc_array(mshell, mshell->num_heredoc))
		return (0);
	signal(SIGINT, handle_heredoc_signal);
	make_heredoc(mshell, temp, mshell->num_heredoc);
	dup2(stdin, STDIN_FILENO);
	if (g_sig == 130)
	{
		mshell->exit_code = 130;
		return (0);
	}
	close(stdin);
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
	while (line[*i] && (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '"'))
	{
		*i += 1;
		j++;
	}
	name = ft_substr(line, start, j);
	node = find_envp(mshell->env_list, name);
	if (!node)
	{
		if (name)
			free(name);
		return ;
	}
	j = -1;
	while (node->content[++j])
		write(fd, &node->content[j], 1);
	free(name);
}
