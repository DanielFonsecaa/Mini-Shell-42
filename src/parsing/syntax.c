#include "../../includes/minishell.h"

int	quote_checker(char *rd_l)
{
	int	i;

	i = 0;
	while (rd_l[i] != '\0')
	{
		if (rd_l[i] == '"')
		{
			if(!count_quote_content(rd_l, &i, rd_l[i]))
					return (0);
		}
		else if (rd_l[i] == '\'')
		{
			if(!count_quote_content(rd_l, &i, rd_l[i]))
					return (0);
		}
		else
			i++;
	}
	return (1);
} 

int	check_pipeline(t_token **token)
{
	t_token *temp;

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
// Eventualmente mudar esta funcao de sitio para algo de utils related
int	check_redir_type(t_token *temp)
{
	return (temp->type == INFILE || temp->type == OUTFILE
		|| temp->type == HERE || temp->type == APPEND);
}

int	syntax_error(t_shell *mshell, t_token **token)
{
	(void)mshell;
	t_token *temp;

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
		}
		temp = temp->next;
	}
	return (1);
}
