#include "../../includes/minishell.h"

void	handle_child_free(t_shell *mshell, t_token **token, char *path)
{
	if (path)
		free(path);
	if (mshell->pids)
		free(mshell->pids);
	free_list(token);
	if (mshell->command)
		free_cmd_struct(mshell);
	free_envp_list(mshell);
	if (mshell->env_var)
		free_arr(mshell->env_var);
	if (mshell->exec_command)
		free_arr(mshell->exec_command);
	if (mshell->fake_cwd)
		free(mshell->fake_cwd);
	if (mshell->rd_l)
		free(mshell->rd_l);
	if (mshell->heredoc_fd)
		free_heredoc(mshell);
	cleanup_pipes(mshell->pipes, mshell->num_commands - 1, mshell);
	mshell->pids = NULL;
	mshell->env_var = NULL;
	mshell->exec_command = NULL;
	mshell->fake_cwd = NULL;
	mshell->rd_l = NULL;
}

/**
 * @brief Free all allocated memory in case of any errors
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	handle_error_shell(t_shell *mshell, t_token **token)
{
	free_list(token);
	if (mshell->command)
		free_cmd_struct(mshell);
	free_envp_list(mshell);
	if (mshell->env_var)
	{
		free_arr(mshell->env_var);
		mshell->env_var = NULL;
	}
	if (mshell->exec_command)
	{
		free_arr(mshell->exec_command);
		mshell->exec_command = NULL;
	}
	if (mshell->fake_cwd)
	{
		free(mshell->fake_cwd);
		mshell->fake_cwd = NULL;
	}
	if (mshell->rd_l)
	{
		free(mshell->rd_l);
		mshell->rd_l = NULL;
	}
}

/**
 * @brief Free all allocated memory associated with the shell structure
 * 
 * @param mshell Pointer to the main shell structure
 * @param token Double pointer to the token list to be freed
 */
void	free_all(t_shell *mshell, t_token **token)
{
	free_list(token);
	if (mshell->command)
		free_cmd_struct(mshell);
	if (mshell->env_var)
	{
		free_arr(mshell->env_var);
		mshell->env_var = NULL;
	}
	if (mshell->exec_command)
	{
		free_arr(mshell->exec_command);
		mshell->exec_command = NULL;
	}
	if (mshell->heredoc_fd)
		free_heredoc(mshell);
	if (mshell->fake_cwd)
	{
		free(mshell->fake_cwd);
		mshell->fake_cwd = NULL;
	}
	if (mshell->rd_l)
	{
		free(mshell->rd_l);
		mshell->rd_l = NULL;
	}
}
