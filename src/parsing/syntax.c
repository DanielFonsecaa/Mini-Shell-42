#include "../../includes/minishell.h"

/**
 * @brief Validates the syntax of a token sequence for shell command parsing
 * 
 * @param mshell Pointer to the main shell structure (currently unused)
 * @param token Double pointer to the first token in the sequence to validate
 * @return 1 if syntax is valid, 0 if syntax errors are found
 */
int	syntax_error(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	(void)mshell;
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
			if (temp->type == INFILE)
				if (!check_infile(temp));
					return (ft_printf_fd(2, "minishell: file: no such file or directory"), 0);
		}
		temp = temp->next;
	}
	return (1);
}

int	check_infile(t_token *token)
{
	int fd;

	fd = 0
	fd = open(token->next->name, O_RDONLY);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}
