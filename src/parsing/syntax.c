#include "../../includes/minishell.h"

int	quote_checker(char *rd_l)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	while (rd_l[i] != '\0')
	{
		if (rd_l[i] == '"')
			double_quotes++;
		else if (rd_l[i] == '\'')
			single_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0)
		return (0);
	if (single_quotes % 2 != 0)
		return (0);
	return (1);
} 

int	check_pipeline(t_token **token)
{
	t_token *temp;

	temp = *token;
	while (temp->next)
	{
		if (temp->type == PIPE && temp->next->type == PIPE)
			return (0);
		temp = temp->next;
	}
}
// Eventualmente mudar esta funcao de sitio para algo de utils related
int	check_rid_type(t_token *temp)
{
	return (temp->type == INFILE || temp->type == OUTFILE
		|| temp->type == HERE || temp->type == APPEND);
}

int	syntax_error(t_shell *mshell, t_token **token)
{
	t_token *temp;

	temp = *token;
	if (!quote_checker(mshell->rd_l))
		return (ft_printf_fd(2, "%s\n", ERR_QUOTE), 0);
	if (!check_pipeline(token))
		return (ft_printf_fd(2, "%s\n", ERR_PIPELINE), 0);
	while (temp)
	{
		if (temp->type == OUTFILE || temp->type == INFILE || temp->type == HERE
			|| temp->type ==  APPEND)
		{
				if (temp->next && check_rid_type(temp->next))
					return (ft_printf_fd(2, "%s\n", ERR_FILE), 0);
		}
		temp = temp->next;
	}

}
