#include "../../includes/minishell.h"

//debug arr of cmd --- erase latetr
static void     print_cmd_arr(t_shell *mshell)
{
	int i = -1;
	int j;
	while (mshell->command[++i])
	{
		ft_printf_fd(1, " name -> %s\n", mshell->command[i]->name);
		j = -1;
		if (mshell->command[i]->flags)
		{
			while (mshell->command[i]->flags[++j]) {
				ft_printf_fd(1, " flag %d -> %s\n", j, mshell->command[i]->flags[j]);
			}
		}
		j = -1;
		if (mshell->command[i]->args)
		{
			while (mshell->command[i]->args[++j]) {
				ft_printf_fd(1, " arg %d -> %s\n", j, mshell->command[i]->args[j]);
			}
		}
	}
}

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
	init_token_data(mshell, token);
	if (!init_shell_data(mshell, token))
		return (0);
	print_cmd_arr(mshell);
	//ft_printf_fd(1, "token size --%i\n num pipes --%i\n", mshell->tokens_size, mshell->num_pipes);
	return (1);
}

void	expansion(t_envp *env_list, t_token **token)
{
	t_token	*temp;
	t_envp	*node;
	char	*name;
	char	*old_token_name;

	temp = *token;
	while (temp)
	{
		//ft_printf("node->content");
		if (temp->name[0] == '$' && temp->type == ARG)
		{
			name = ft_substr(temp->name, 1, ft_strlen(temp->name));
			node = find_envp(env_list, name);
			free(name);
			if (!node)
				return ; // Error in here please
			name = node->content;
			old_token_name = temp->name;
			temp->name = name;
			free(old_token_name);
			free(node);
		}
		temp = temp->next;
	}
}
