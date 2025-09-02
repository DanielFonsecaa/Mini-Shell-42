#include "../../includes/minishell.h"

/**
 * @brief Handles the pwd built-in command
 * 
 * @param mshell Pointer to the shell structure containing exit code and state
 * @param token Double pointer to the current token (pwd command token)
 */
void handle_pwd(t_shell *mshell, t_token **token, int fd)
{
	char	*cwd;
	t_token	*temp;

	temp = *token;
	if (temp->next && temp->next->type != PIPE && temp->next->name[0] == '-')
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, ERR_NO_FLAG_ALLOWED);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		mshell->exit_code = 1;
		ft_printf_fd(2, ERR_PWD);
		return ;
	}
	ft_printf_fd(fd, "%s\n", cwd);
	free(cwd);
	mshell->exit_code = 0;
}
