#include "../../includes/minishell.h"

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
 * @brief Counts the number of pipe tokens in the token
 * 
 * @param mshell Pointer to the shell structure to update
 * 		with pipe information
 * @param token Pointer to pointer to the first token
 * 		in the linked list
 */
void	pipe_count(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	mshell->num_pipes = 0;
	mshell->num_redirecs = 0;
	mshell->has_pipes = false;
	mshell->has_redirect = false;
	temp = *token;
	while (temp)
	{
		if (temp->type == PIPE)
			mshell->num_pipes++;
		if (temp->type == APPEND || temp->type == INFILE
			|| temp->type == OUTFILE || temp->type == HERE)
			mshell->num_redirecs++;
		temp = temp->next;
	}
	if (mshell->num_pipes > 0)
		mshell->has_pipes = true;
	if (mshell->num_redirecs > 0)
		mshell->has_redirect = true;
}
