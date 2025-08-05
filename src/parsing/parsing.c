#include "../../includes/minishell.h"

/**
 * @brief Counts the number of pipe tokens in the token list and sets pipe flags
 * 
 * @param mshell Pointer to the shell structure to update with pipe information
 * @param token Pointer to pointer to the first token in the linked list
 */
void	pipe_count(t_shell *mshell, t_token **token)
{
	t_token	*temp;
//	t_token	*pipe;

	mshell->num_pipes = 0;
	mshell->has_pipes = false;
	mshell->closed_pipe = true;
	temp = *token;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			mshell->num_pipes++;
			temp->is_pipe = true;
			temp->last_pipe = false;
		}
		else
		{
			temp->is_pipe = false;
			temp->last_pipe = false;
		}
		if (temp->type == PIPE && temp->next == NULL)
			mshell->closed_pipe = false;
		temp = temp->next;
	}
	if (mshell->num_pipes > 0)
		mshell->has_pipes = true;
//	pipe->last_pipe = true;
}

/**
 * @brief Parses the command line input and processes tokens for the minishell
 * 
 * @param mshell Pointer to the main shell structure containing shell state
 * @param token Double pointer to the token list that will be populated
 */
void	parsing(t_shell *mshell, t_token **token)
{
	tokenize(mshell->rd_l, token);
	mshell->tokens_size = token_list_size(*token);
	set_t_type(token);
	type_file(token);
	print_list(token);
	pipe_count(mshell, token);
	ft_printf_fd(1,"token size --%i\n num pipes --%i\n", mshell->tokens_size,
		mshell->num_pipes);
}
