#include "../../includes/minishell.h"

int	is_meta_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

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

void	print_list(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		ft_printf("%d$", current->type);
		current = current->next;
	}
	ft_printf("\n");
}
