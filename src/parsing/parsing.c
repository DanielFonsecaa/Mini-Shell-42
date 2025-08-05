#include "../../includes/minishell.h"

/**
 * @brief Parses the command line input and processes tokens for the minishell
 * 
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to the token list that will be populated
 */
int	parsing(t_shell *mshell, t_token **token)
{
	if (!quote_checker(mshell->rd_l))
		return (ft_printf_fd(2, ERR_QUOTE), 0);
	if (!tokenize(mshell->rd_l, token))
		return (0);
	mshell->tokens_size = token_list_size(*token);
	set_t_type(token);
	type_file(token);
	print_list(token);
	pipe_count(mshell, token);
	if (!syntax_error(mshell, token))
		return (0);
	ft_printf_fd(1, "token size --%i\n num pipes --%i\n", mshell->tokens_size,
		mshell->num_pipes);
	return (1);
}
