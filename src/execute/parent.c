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
	if (mshell->num_commands == 0)
	{
		handle_redirections(mshell, token, temp);
	}
	while (++i < mshell->num_commands)
	{
		mshell->pids[i] = fork();
		if (mshell->pids[i] == -1)
			return (perror("fork"));
		if (mshell->pids[i] == 0)
		{
			setup_child(mshell, i, mshell->fd, *token);
			handle_redirections(mshell, token, temp);
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

void	handle_redirections(t_shell *mshell, t_token **head, t_token *token)
{
	t_ints	ints;

	ints.flags = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == INFILE && !(mshell->heredoc_fd != NULL && mshell->num_heredoc > 0))
		{
			ints.flags = O_RDONLY;
			ints.fd = STDIN_FILENO;
			helper_handle_redir(mshell, token, head, ints);
		}
		else if (token->type == OUTFILE)
		{
			ints.flags = O_WRONLY | O_CREAT | O_TRUNC;
			ints.fd = STDOUT_FILENO;
			helper_handle_redir(mshell, token, head, ints);
		}
		else if (token->type == APPEND)
		{
			ints.flags = O_WRONLY | O_CREAT | O_APPEND;
			ints.fd = STDOUT_FILENO;
			helper_handle_redir(mshell, token, head, ints);
		}
		token = token->next;
	}
	if (mshell->num_commands == 0)
	{
		close(ints.fd);
	}
}

void	helper_handle_redir(t_shell *mshell, t_token *token, t_token **head, t_ints ints)
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
		expanded_name = ft_strdup(token->next->name);
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
		if (!open_file_and_dup(expanded_name, ints.fd, ints.flags))
		{
			handle_child_free(mshell, head, expanded_name);
			exit(ERROR);
		}
		if (mshell->num_commands == 0)
			close(ints.fd);
	}
	if (!token->next->has_quote && expanded_name)
		free(expanded_name);
}

int	open_file_and_dup(char	*file_name, int fd, int flags)
{
	int	new_fd;

	new_fd = open(file_name, flags, 0644);
	if (new_fd == -1)
	{
		ft_printf_fd(2, ERR_NO_FILE, file_name);
//		perror("open");
		return (0);
	}
	dup2(new_fd, fd);
	close(new_fd);
	return (1);
}
