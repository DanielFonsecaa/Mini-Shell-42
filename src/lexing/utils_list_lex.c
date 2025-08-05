#include "../../includes/minishell.h"

/**
 * @brief Creates a new token structure with the given content.
 *
 * @param content The string content to be stored in the token
 * @return A pointer to the newly created token structure,
 * 			or NULL if allocation fails
 */
t_token	*ft_newtoken(char *content)
{
	t_token	*token;

	token = safe_calloc(1, sizeof(t_token));
	token->name = ft_strdup(content);
	if (has_quote(token->name))
		token->has_quote = true;
	else
		token->has_quote = false;
	token->next = NULL;
	return (token);
}

/**
 * @brief Adds a new token to the end of a linked list of tokens
 * 
 * @param token Double pointer to the head of the token list
 * @param new_token Pointer to the new token to be added to the list
 */
void	token_addback(t_token **token, t_token *new_token)
{
	t_token	*last;

	if (token)
	{
		if (*token)
		{
			last = token_lst_last(*token);
			last->next = new_token;
			new_token->prev = last;
		}
		else
		{
			new_token->prev = NULL;
			*token = new_token;
		}
	}
}

/**
 * @brief Finds and returns the last token in a linked list of tokens.
 *
 * @param token Pointer to the first token in the linked list
 * @return t_token* Pointer to the last token in the list,
 * 			or NULL if the input is NULL
 */
t_token	*token_lst_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

/**
 * @brief Calculates the size of a token linked list
 * 
 * @param token Pointer to the first token in the linked list
 * @return int The number of tokens in the list, or 0 if the list is empty
 */
int	token_list_size(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
