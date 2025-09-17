#include "../../includes/minishell.h"

/**
 * @brief Executes a pipeline of commands
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to token array used for command execution
 */
void	execute_pipe_redirect(t_shell *mshell, t_token **token)
{
	int		i;
	t_token	*temp;

	i = -1;
	temp = *token;
	while (++i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			return (perror("fork"));
		if (mshell->pids[i] == 0)
		{
			setup_child(mshell, i, mshell->fd);
			handle_redirections(mshell, temp);
			exec_child_cmd(mshell, &temp, token, mshell->command[i]);
		}
		if (i > 0)
			close(mshell->pipes[i - 1][0]);
		if (i < mshell->num_commands - 1)
			close(mshell->pipes[i][1]);
		while (temp && temp->type != PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
}

/**
 * @brief Handles input/output redirections for shell commands
 *
 * @param token Pointer to the first token in the token list to process
 * @param fd Array of file descriptors [0] for input, [1] for output
 */

void	handle_redirections(t_shell *mshell, t_token *token)
{
	int		flags;

	while (token && token->type != PIPE)
	{
		if (token->type == INFILE)
		{
			flags = O_RDONLY;
			helper_handle_redir(mshell, token, flags, STDIN_FILENO);
		}
		else if (token->type == OUTFILE)
		{
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			helper_handle_redir(mshell, token, flags, STDOUT_FILENO);
		}
		else if (token->type == APPEND)
		{
			flags = O_WRONLY | O_CREAT | O_APPEND;
			helper_handle_redir(mshell, token, flags, STDOUT_FILENO);
		}
		token = token->next;
	}
}

void	helper_handle_redir(t_shell *mshell, t_token *token, int flags, int fd)
{
	char	*expanded_name;
	int		is_error;

	expanded_name = NULL;
	is_error = 0;
	if (!token->next)
		return ;
	if (token->next->has_quote)
	{
		expand_quoted_token(mshell, token->next);
		expanded_name = token->next->name;
	}
	else
	{
		expanded_name = expand_token_content(mshell, token->next);
		if (expanded_name && ft_strchr(expanded_name, ' '))
		{
			ft_printf_fd(2, ERR_AMBIGUOUS, expanded_name);
			is_error = 1;
		}
	}
	if (!is_error && expanded_name)
	{
		if (!open_file_and_dup(expanded_name, fd, flags, token->type))
		{
			return (0);
		}
	}
	if (!token->next->has_quote && expanded_name)
		free(expanded_name);
}

int	open_file_and_dup(char	*file_name, int fd, int flags, int type)
{
	int	new_fd;

	new_fd = open(file_name, flags, 0644);
	if (new_fd == -1)
	{
		perror("open");
		return (0);
	}
	dup2(new_fd, fd);
	close(new_fd);
	return (1);
}
