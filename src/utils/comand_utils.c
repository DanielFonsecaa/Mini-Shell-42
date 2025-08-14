#include "../../includes/minishell.h"

void    count_num_commands(t_shell *mshell, t_token **token)
{
	t_token *temp;
	int     i;

	i = 0;
	temp = *token;
	while (temp)
	{
		if (temp->type == CMD)
			i++;
		temp = temp->next;
	}
	mshell->num_commands = i;
}