#include "../../includes/minishell.h"

/**
 * @brief Handles the pwd built-in command to print the
 * 			current working directory
 *
 * @param token Double pointer to the token structure containing
 * 				the command and arguments
 * @return 0 on success, 1 on error
 */
int	handle_pwd(t_token **token)
{
	char	*cwd;
	t_token	*temp;

	temp = *token;
	if (temp->next && temp->next->type != PIPE && temp->next->name[0] == '-')
		return (ft_printf_fd(2, "Error: No flags allowed with pwd\n"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_printf_fd(2, "pwd: Error retrieving directory\n"), 1);
	ft_printf_fd(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
