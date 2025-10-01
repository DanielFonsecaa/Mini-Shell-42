/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:21 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:39:22 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_child_input(t_shell *mshell, int index,
	int *fd, t_token *token)
{
	int	heredoc_fd;

	if (mshell->heredoc_fd != NULL && mshell->num_heredoc > 0
		&& command_has_heredoc(token, index))
	{
		heredoc_fd = get_command_heredoc_fd(mshell, token, index);
		if (heredoc_fd >= 0)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
	}
	else if (index == 0)
	{
		if (fd && fd[0] > 2)
			dup2(fd[0], STDIN_FILENO);
	}
	else
		dup2(mshell->pipes[index - 1][0], STDIN_FILENO);
}

/**
 * @brief Search for the full path of a command
 *
 * @param envp Array of environment variables
 * @param cmd The command name to search for
 * @return Returns the full path to the executable if found or NULL
 */

char	*find_executable_in_path(char **full_path, char *cmd)
{
	int			i;
	char		*half_path;
	char		*path;
	struct stat	st;

	i = 0;
	while (full_path[i])
	{
		half_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			{
				free(path);
				i++;
				continue ;
			}
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Checks if the command at index has heredocs
 *
 * @param token Pointer to the token list
 * @param target_index The command index to check for heredocs
 * @return 1 if this command has heredocs, 0 otherwise
 */
int	command_has_heredoc(t_token *token, int target_index)
{
	t_token	*temp;
	int		current_cmd_index;

	temp = token;
	current_cmd_index = 0;
	while (temp && current_cmd_index < target_index)
	{
		if (temp->type == PIPE)
			current_cmd_index++;
		temp = temp->next;
	}
	while (temp && temp->type != PIPE)
	{
		if (temp->type == HERE)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/**
 * @brief Finds the last heredoc fd for a specific command in the pipeline
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to the token list
 * @param target_index The command index to find heredoc for
 * @return The fd of the last heredoc for this command, or -1 if none
 */
int	get_command_heredoc_fd(t_shell *mshell, t_token *token,
				int target_index)
{
	t_token	*temp;
	int		current_cmd_index;
	int		heredoc_index;
	int		last_heredoc_fd;

	temp = token;
	current_cmd_index = 0;
	heredoc_index = 0;
	last_heredoc_fd = -1;
	while (temp)
	{
		if (temp->type == PIPE)
			current_cmd_index++;
		else if (temp->type == HERE && current_cmd_index == target_index)
		{
			if (heredoc_index < mshell->num_heredoc
				&& mshell->heredoc_fd[heredoc_index] >= 0)
				last_heredoc_fd = mshell->heredoc_fd[heredoc_index];
			heredoc_index++;
		}
		else if (temp->type == HERE)
			heredoc_index++;
		temp = temp->next;
	}
	return (last_heredoc_fd);
}

/**
 * @brief Formats a command structure into an executable command array.
 *
 * @param mshell Pointer to the shell structure
 * @param command Pointer to the command structure
 */
void	format_cmd(t_shell *mshell, t_cmd *command)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (command->name)
		size++;
	i = 0;
	while (command->args && command->args[i++])
		size++;
	mshell->exec_command = safe_calloc(size + 1, sizeof(char *));
	size = 0;
	i = 0;
	if (command->name)
		mshell->exec_command[i++] = ft_strdup(command->name);
	while (command->args && command->args[size])
		mshell->exec_command[i++] = ft_strdup(command->args[size++]);
}
