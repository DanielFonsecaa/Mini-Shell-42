#include "../../includes/minishell.h"

/**
 * @brief Validates the syntax of a token sequence for shell command parsing
 * 
 * @param mshell Pointer to the main shell structure (currently unused)
 * @param token Double pointer to the first token in the sequence to validate
 * @return 1 if syntax is valid, 0 if syntax errors are found
 */
int	syntax_error(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (!check_pipeline(token))
		return (ft_printf_fd(2, ERR_PIPELINE), 0);
	while (temp)
	{
		if (check_redir_type(temp))
		{
			if (temp->next && check_redir_type(temp->next))
				return (ft_printf_fd(2, ERR_REDIRECT), 0);
			if (!temp->next)
				return (ft_printf_fd(2, ERR_SYNTAX), 0);
			if (temp->type == INFILE)
				if (!check_infile(temp))
					return (ft_printf_fd(2, ERR_NO_FILE, temp->next->name), 0);
			if (!check_perms(mshell, temp))
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}

/**
 * @brief Validates the pipeline syntax in a token list
 *
 * @param token Double pointer to the first token in the linked list
 * @return int Returns 1 if pipeline syntax is valid, 0 if invalid
 */
int	check_pipeline(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		if (temp->next && temp->type == PIPE && temp->next->type == PIPE)
			return (0);
		if (temp->type == PIPE && !temp->next)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_perms(t_shell *mshell, t_token *token)
{
	int		return_val;
	char	*pathname;

	if (token->name[0] == '/')
		pathname = ft_strdup(token->next->name);
	else
	{
		pathname = ft_strjoin(mshell->curr_wd, "/");
		pathname = ft_strjoin_free(pathname, token->next->name);
	}
	if (token->type == INFILE)
	{
		return_val = access(pathname, R_OK);
		if (return_val != 0)
		{
			ft_printf_fd(2, ERR_NO_PERMS, token->next->name);
			free(pathname);
			return (0);
		}
	}
	else if (token->type == OUTFILE || token->type == APPEND)
	{
		if (access(pathname, F_OK) == 0)
		{
			return_val = access(pathname, W_OK);
			if (return_val != 0)
			{
				ft_printf_fd(2, ERR_NO_PERMS, token->next->name);
				free(pathname);
				return (0);
			}
		}
	}
	free(pathname);
	return (1);
}

/**
 * @brief Checks if quotes in a string are properly balanced and closed
 *
 * @param rd_l The input string to check for balanced quotes
 * @return 1 if all quotes are properly balanced and closed, 0 otherwise
 */
int	quote_checker(char *rd_l)
{
	int	i;

	i = 0;
	while (rd_l[i] != '\0')
	{
		if (rd_l[i] == '"' || rd_l[i] == '\'')
		{
			if (!skip_inside_quotes(rd_l, &i, rd_l[i]))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

/**
 * @brief Checks if a token represents a redirection operator
 *
 * @param temp Pointer to the token to be checked
 * @return int Returns 1 if the token is a redirection type, 0 if not
 */
int	check_redir_type(t_token *temp)
{
	return (temp->type == INFILE || temp->type == OUTFILE
		|| temp->type == HERE || temp->type == APPEND);
}

int	check_infile(t_token *token)
{
	int		fd;
	t_token	*temp;

	temp = token;
	fd = open(temp->next->name, O_RDONLY);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}
