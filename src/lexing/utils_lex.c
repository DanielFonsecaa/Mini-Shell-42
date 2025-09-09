#include "../../includes/minishell.h"

/**
 * @brief Checks if a character is a shell metacharacter
 * 
 * @param c The character to check
 * @return int Returns 1 if the character is a metacharacter ('<', '>', '|'),
 *             0 otherwise
 */
int	is_meta_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

/**
 * @brief Checks if a string contains any quote characters (single or double).
 * 
 * @param str The null-terminated string to check for quotes
 * @return int Returns 1 if at least one quote character is found, 0 otherwise
 */
int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Prints the types of all tokens in a linked list
 * 
 * @param token Double pointer to the head of the token linked list
 */
void	print_list(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		ft_printf_fd(1, "%d$", current->type);
		current = current->next;
	}
	ft_printf_fd(1, "\n");
}

/**
 * @brief Counts and skips over quoted content in a string
 * 
 * @param rd_l The input string to parse
 * @param j Pointer to the current index position, will be updated to
 * 			position after closing quote
 * @param c The quote character to match
 * @return 1 if a matching closing quote was found,
 * 			0 if the string ended without a closing quote
 */
int	skip_inside_quotes(char *rd_l, int *j, char c)
{
	int	i;

	i = *j + 1;
	while (rd_l[i] && rd_l[i] != c)
		i++;
	if (!rd_l[i])
		return (0);
	*j = i + 1;
	return (1);
}

void	set_t_arg(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == TFILE)
		return ;
	if (temp->type == LIMITER)
		return ;
	temp->type = ARG;
	if (temp->name[0] == '-')
		temp->type = FLAG;
}
