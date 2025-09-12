#include "../../includes/minishell.h"

/**
 * @brief Executes a command, either built-in or external
 *
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_cmd_line(t_shell *mshell, t_token **token)
{
	if (is_built_in(token) && !mshell->has_pipes && !mshell->has_redirect)
	{
		format_cmd(mshell, mshell->command[0]);
		execute_built_in(mshell, token);
	}
	else
		execute_with_pipes_or_redirect(mshell, token);
}

/**
 * @brief Executes commands with pipes or redirections
 *
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_with_pipes_or_redirect(t_shell *mshell, t_token **token)
{
	if (mshell->has_pipes || mshell->has_redirect)
	{
		init_pipeline(mshell);
		execute_pipe_redirect(mshell, token);
		cleanup_and_wait(mshell);
		return ;
	}
	mshell->pids = safe_malloc(sizeof(pid_t));
	mshell->pids[0] = fork();
	if (mshell->pids[0] == -1)
	{
		perror("fork");
		free(mshell->pids);
		mshell->pids = NULL;
		return ;
	}
	if (mshell->pids[0] == 0)
	{
		handle_redirections(mshell, *token);
		exec_child_cmd(mshell, token, token, mshell->command[0]);
	}
	wait_and_get_exit_status(mshell);
	if (mshell->pids)
		free(mshell->pids);
	mshell->pids = NULL;
}

/**
 * @brief Executes built-in shell commands
 * 
 * @param mshell Pointer to the shell structure
 * @param token Double pointer to the token structure
 */
void	execute_built_in(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (ft_strcmp(temp->name, "echo") == 0)
		handle_echo(mshell);
	else if (ft_strcmp(temp->name, "env") == 0)
		handle_env(mshell);
	else if (ft_strcmp(temp->name, "pwd") == 0)
		handle_pwd(mshell, token);
	else if (ft_strcmp(temp->name, "exit") == 0)
		handle_exit(mshell, token);
	else if (ft_strcmp(temp->name, "cd") == 0)
		handle_cd(mshell, token);
	else if (ft_strcmp(temp->name, "export") == 0)
		handle_export(mshell, token);
	else if (ft_strcmp(temp->name, "unset") == 0)
		handle_unset(mshell, token);
}
