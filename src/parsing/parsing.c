#include "../../includes/minishell.h"

void	pipe_count(t_shell *mshell, t_token **token)
{
	t_token *temp;

	temp = *token;
	while (temp)
	{
		if (temp->type == PIPE)
			mshell->num_pipes++;
		temp = temp->next;
	}
	if (mshell->num_pipes > 0)
		mshell->has_pipes = true;
}
