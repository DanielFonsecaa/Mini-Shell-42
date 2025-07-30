#include "../../includes/minishell.h"
// free all function
/*void	free_shell()
{

}*/

void	handle_error_shell(t_shell *mshell, t_token **token)
{
	free_list(token);
	free_envp(mshell->env_var);
	free(mshell->fake_cwd);
	free(mshell->rd_l);
}	

void	free_loop(t_shell *mshell, t_token **token)
{
	free_list(token);
	free_envp(mshell->env_var);
	free(mshell->fake_cwd);
	free(mshell->rd_l);
}

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

void	free_envp(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}
