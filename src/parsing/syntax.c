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

	(void)mshell;
	temp = *token;
	if (!check_pipeline(token))
		return (0);
	while (temp)
	{
		if (check_redir_type(temp))
		{
			if (temp->next && check_redir_type(temp->next))
				return (0);
			if (!temp->next)
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
	if (temp)
	{
		if (!temp->prev && temp->type == PIPE)
			return (0);
	}
	while (temp)
	{
		if (!(temp->has_quote))
		{
			if (temp->next && (temp->type == PIPE
					|| check_redir_type(temp)) && temp->next->type == PIPE)
				return (0);
		}
		if (!(temp->has_quote))
		{
			if (temp->type == PIPE && !temp->next)
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	check_perms(t_shell *mshell, t_token *token)
{
	char	*path_name;

	if (token->name[0] == '/')
		path_name = ft_strdup(token->next->name);
	else
	{
		path_name = ft_strjoin(mshell->curr_wd, "/");
		path_name = ft_strjoin_free(path_name, token->next->name);
	}
	if (token->type == INFILE)
	{
		if (access(path_name, R_OK) != 0)
			return (helper_check_perms(token->next->name, path_name));
	}
	else if (token->type == OUTFILE || token->type == APPEND)
	{
		if (access(path_name, F_OK) == 0)
		{
			if (access(path_name, W_OK) != 0)
				return (helper_check_perms(token->next->name, path_name));
		}
	}
	free(path_name);
	return (1);
}

int	helper_check_perms(char *token_name, char *path_name)
{
	(void)token_name;
	free(path_name);
	return (0);
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
