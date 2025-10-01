/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:40 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:39:41 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	temp = *token;
	i = -1;
	if (mshell->num_commands == 0)
		handle_single_command(mshell, token, temp);
	while (++i < mshell->num_commands)
	{
		temp = get_command(*token, i);
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
	}
}

/**
 * @brief Handles input/output redirections for shell commands
 *
 * @param token Pointer to the first token in the token list to process
 * @param fd Array of file descriptors [0] for input, [1] for output
 */

void	handle_redirections(t_shell *ms, t_token **head, t_token *tok)
{
	t_ints	ints;

	ints.flags = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == 3 && !(ms->heredoc_fd != NULL && ms->num_heredoc > 0))
		{
			ints.flags = O_RDONLY;
			ints.fd = STDIN_FILENO;
			helper_handle_redir(ms, tok, head, ints);
		}
		else if (tok->type == OUTFILE)
		{
			ints.flags = O_WRONLY | O_CREAT | O_TRUNC;
			ints.fd = STDOUT_FILENO;
			helper_handle_redir(ms, tok, head, ints);
		}
		else if (tok->type == APPEND)
		{
			ints.flags = O_WRONLY | O_CREAT | O_APPEND;
			ints.fd = STDOUT_FILENO;
			helper_handle_redir(ms, tok, head, ints);
		}
		tok = tok->next;
	}
}

static char	*expand_redir_filename(t_shell *mshell, t_token *token, int *is_er)
{
	char	*expanded_name;

	expanded_name = NULL;
	*is_er = 0;
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
			*is_er = 1;
		}
	}
	return (expanded_name);
}

void	helper_handle_redir(t_shell *ms, t_token *token,
		t_token **head, t_ints ints)
{
	char	*expanded_name;
	int		is_error;

	if (!token->next)
		return ;
	expanded_name = expand_redir_filename(ms, token, &is_error);
	if (!is_error && expanded_name)
	{
		if (!open_file_and_dup(expanded_name, ints.fd, ints.flags, ms)
			&& ms->num_commands > 0)
		{
			handle_child_free(ms, head, expanded_name);
			exit(ERROR);
		}
	}
	if (!token->next->has_quote && expanded_name)
		free(expanded_name);
}

int	open_file_and_dup(char	*file_name, int fd, int flags, t_shell *mshell)
{
	int	new_fd;

	new_fd = open(file_name, flags, 0644);
	if (new_fd == -1)
	{
		ft_printf_fd(2, ERR_NO_FILE, file_name);
		mshell->exit_code = 1;
		return (0);
	}
	dup2(new_fd, fd);
	close(new_fd);
	return (1);
}
