#include "../../includes/minishell.h"

/**
 * @brief Checks if a command name matches a given command string.
 * 
 * @param name The command name to check
 * @param cmd The reference command string to compare against
 * @return int Returns 1 if the strings match, 0 otherwise
 */
static int	is_command(char *name, char *cmd)
{
	return (ft_strcmp(name, cmd) == 0);
}

/**
 * @brief Checks if a token represents a built-in command.
 *
 * @param token Double pointer to a t_token structure
 * @return int Returns 1 if the token is a built-in, 0 if not.
 */
int	is_built_in(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (is_command(temp->name, "echo")
		|| is_command(temp->name, "env")
		|| is_command(temp->name, "pwd")
		|| is_command(temp->name, "exit")
		|| is_command(temp->name, "cd")
		|| is_command(temp->name, "export")
		|| is_command(temp->name, "unset"))
		return (1);
	return (0);
}
