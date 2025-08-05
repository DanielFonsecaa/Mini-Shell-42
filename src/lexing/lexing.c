#include "../../includes/minishell.h"

/**
 * @brief Creates and adds the first token to the token list from a given line
 * 
 * @param token Double pointer to the token list where the new token will be added
 * @param line Source string from which to extract the token content
 * @param size Number of characters to extract from the beginning of line
 */
void	ft_first_token(t_token **token, char *line, int size)
{
	char	*str;
	int		i;

	str = safe_malloc(size + 1);
	i = 0;
	str[size] = '\0';
	while (i < size)
	{
		str[i] = line[i];
		i++;
	}
	token_addback(token, ft_newtoken(str));
	free(str);
}

/**
 * @brief Tokenizes a command line string into a linked list of tokens
 * 
 * @param rd_l The input command line string to tokenize
 * @param token Pointer to the token list where new tokens will be added
 * 
 * The function performs the following operations:
 * 1. Skips whitespace characters
 * 2. Identifies word tokens (non-whitespace, non-metacharacter sequences)
 * 3. Identifies metacharacter token sequences
 * 4. Creates tokens for both words and metacharacter groups
 */
void	tokenize(char *rd_l, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	while (rd_l[i])
	{
		while (ft_iswhite_space(rd_l[i]))
			i++;
		j = 0;
		while (rd_l[i + j] && !ft_iswhite_space(rd_l[i + j])
			&& !is_meta_char(rd_l[i + j]))
			j++;
		if ((rd_l[i] || rd_l[i + j]) && !is_meta_char(rd_l[i]))
			ft_first_token(token, rd_l + i, j);
		i += j;
		j = 0;
		while (is_meta_char(rd_l[i + j]))
			j++;
		if (is_meta_char(rd_l[i + j - 1]))
			ft_first_token(token, rd_l + i, j);
		i += j;
	}
}
/**
 * @brief Sets the token type for each token in a linked list based on token content and position
 * 
 * @param token Double pointer to the first token in the linked list
 */

void	set_t_type(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		ft_printf_fd(1, "value %s\n", temp->name);
		if (ft_strcmp(temp->name, "<<") == 0)
			temp->type = HERE;
		else if (ft_strcmp(">>", temp->name) == 0)
			temp->type = APPEND;
		else if (ft_strcmp(">", temp->name) == 0)
			temp->type = OUTFILE;
		else if (ft_strcmp("<", temp->name) == 0)
			temp->type = INFILE;
		else if (temp->prev == NULL || (temp->prev->type == PIPE
				&& ft_strcmp(temp->name, "|") != 0))
			temp->type = CMD;
		else if (ft_strcmp("|", temp->name) == 0)
			temp->type = PIPE;
		else
			temp->type = ARG;
		temp = temp->next;
	}
}

/**
 * @brief Updates token types to identify file arguments following redirection operators
 * 
 * @param token Double pointer to the head of the token linked list
 */
void	type_file(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		if (temp->prev)
		{
			if ((temp->prev->type == APPEND || temp->prev->type == INFILE
					|| temp->prev->type == OUTFILE) && temp->type == ARG)
				temp->type = TFILE;
		}
		temp = temp->next;
	}
}
