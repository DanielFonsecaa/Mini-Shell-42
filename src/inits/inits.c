#include "../../includes/minishell.h"

/**
 * @brief Initializes shell environment variables and current working directory
 * 
 * @param mshell Pointer to the shell structure to initialize
 * @param envp Array of environment variable strings to copy
 */
void	init_shell_envp_cwd(t_shell *mshell, char **envp)
{
	mshell->env_var = ft_copy_envp(envp);
	getcwd(mshell->curr_wd, sizeof(mshell->curr_wd));
	mshell->fake_cwd = ft_strjoin(mshell->curr_wd, " 👉 ");
}

/**
 * @brief Initializes shell data structure with parsed tokens
 * 
 * @param mshell Pointer to the shell data structure to initialize
 * @param token Pointer to pointer of the first token in the token list
 * @return 1 on successful initialization, 0 if syntax error is detected
 */
int	init_shell_data(t_shell *mshell, t_token **token)
{
	mshell->tokens_size = token_list_size(*token);
	pipe_and_redirects_count(mshell, token);
	if (!syntax_error(mshell, token))
		return (0);
	mshell->num_commands = count_num_commands(token);
	mshell->command = set_cmd_arr(mshell, token);
	mshell->fd[0] = -1;
	mshell->fd[1] = -1;
	return (1);
}

/**
 * @brief Initializes token data by setting token types and file associations
 *
 * @param token Double pointer to the head of the token list to be initialized
 */
void	init_token_data(t_shell *mshell, t_token **token)
{
	set_t_type(token);
	expansion(mshell, token); //test
	type_file(token);
	print_list(token);
}

/**
 * @brief Initializes the pipeline for command execution in the minishell.
 *
 * @param mshell Pointer to the shell structure
 */
void	init_pipeline(t_shell *mshell)
{
	// falta lidar com erros no create pipes caso falhe
	create_pipes(mshell->num_commands - 1, mshell);
	mshell->pids = safe_malloc(sizeof(pid_t) * mshell->num_commands);
	if (!mshell->pids)
	{
		// ft_printf_fd(); display error
		// mshell->exit_code = X; and return ;
	}
}