#include "../../includes/minishell.h"

/**
 * @brief Free all allocated memory in case of any errors
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	handle_error_shell(t_shell *mshell, t_token **token)
{

	if (token)
		free_list(token);
	if (mshell->command)
		free_cmd_struct(mshell->command);
	if (mshell->env_list)
		free_envp_list(mshell->env_list);
	if (mshell->env_var)
		free_arr(mshell->env_var);
	if (mshell->exec_command)
		free(mshell->exec_command); ////////////
	if (mshell->fake_cwd)
		free(mshell->fake_cwd);
	if (mshell->rd_l)
		free(mshell->rd_l);
}

/**
 * @brief Free all allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	free_all(t_shell *mshell, t_token **token)
{
	if (token)
		free_list(token);
	if (mshell->command)
	{
		free_cmd_struct(mshell->command);
		mshell->command = NULL;
	}
//	free_envp_list(mshell->env_list);
	if (mshell->env_var)
		free_arr(mshell->env_var);
	if (mshell->exec_command)
		free(mshell->exec_command); ////////////
	if (mshell->fake_cwd)
		free(mshell->fake_cwd);
	if (mshell->rd_l)
		free(mshell->rd_l);
}