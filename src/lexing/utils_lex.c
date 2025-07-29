#include "../../includes/minishell.h"

int	is_meta_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	increment_token(char line)
{
	return ((ft_iswhite_space(line) || is_meta_char(line)));
}

t_token	*ft_newtoken(char *content)
{
	t_token *token;

	token = safe_calloc(1, sizeof(t_token));
	token->name = ft_strdup(content);
	if (ft_has_quote(token->name)
		token->has_quote = true;
	else
		token->has_quote = false;
	token->next = NULL;
	return (token);
}

void	token_addback(t_token **token, t_token new_token)
{
	t_token *last;

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

t_token *token_lst_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
