#include "../../includes/minishell.h"
// free all function
/*void	free_shell()
{

}*/

void	free_list(t_token **token)
{
	t_token	*temp;

	if (token)
	{
		if (*token)
		{
			while (*token)
			{
				temp = (*token)->next;
				free((*token)->name);
				free(*token);
				*token = temp;
			}
			*token = NULL;
		}
	}
}
