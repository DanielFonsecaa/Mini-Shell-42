#include "../../includes/minishell.h"

/**
 * @brief Handles the pwd built-in command to print the
 * 			current working directory
 *
 * @param token Double pointer to the token structure containing
 * 				the command and arguments
 * @return 0 on success, 1 on error
 */
void	handle_pwd(t_shell *mshell, t_token **token)
{
	char	*cwd;
	t_token	*temp;

	temp = *token;
	if (temp->next && temp->next->type != PIPE && temp->next->name[0] == '-')
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "Error: No flags allowed with pwd\n");
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, "pwd: Error retrieving directory\n");
		return ;
	}
	ft_printf_fd(1, "%s\n", cwd);
	free(cwd);
	mshell->exit_code = 0;
}
