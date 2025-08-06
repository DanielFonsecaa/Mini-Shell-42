#include "../../../includes/minishell.h"

void	handle_export(t_shell *mshell, t_token **token)
{
		t_token	*temp;

		temp = *token;
		if (!temp->next)
			show_export(mshell->env_list); //show all
/*		else
			update_export(); // show only exported ones*/
		mshell->exit_code = 0; 
}
