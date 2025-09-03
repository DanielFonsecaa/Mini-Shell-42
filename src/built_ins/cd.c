#include "../../includes/minishell.h"

/**
 * @brief Handles the cd command in the minishell
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to pointer of the token list
 */
void	handle_cd(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = (*token)->next;
	if (token_list_size(temp) > 1)
	{
		ft_printf_fd(2, ERR_CD_ARGS);
		mshell->exit_code = 1;
	}
	else if (token_list_size(temp) == 0 || ft_strcmp(temp->name, "--") == 0)
		cd_to_key(mshell, "HOME");
	else if (!cd_syntax(mshell, &temp))
		mshell->exit_code = 2;
	else if (ft_strcmp(temp->name, "-") == 0)
	{
		cd_to_key(mshell, "OLDPWD");
		ft_printf_fd(1, "%s\n", mshell->curr_wd);
	}
	else
		change_dir(mshell, &temp);
}

/**
 * @brief Changes the current directory to the specified path.
 *
 * @param mshell Pointer to the shell structure
 * @param token Pointer to the token containing the target directory path
 */
void	change_dir(t_shell *mshell, t_token **token)
{
	char	buffer[PATH_MAX];
	t_token	*path;

	path = *token;
	if (access(path->name, F_OK | X_OK) != 0)
	{
		if (access(path->name, F_OK) != 0)
			ft_printf_fd(2, ERR_NO_FILE, path->name);
		else
			ft_printf_fd(2, ERR_NO_PERMS, path->name);
		mshell->exit_code = 1;
		return ;
	}
	if (chdir(path->name) == -1)
	{
		ft_printf_fd(2, ERR_NO_FILE, path->name);
		mshell->exit_code = 1;
		return ;
	}
	update_envp_with_string(mshell, "OLDPWD", mshell->curr_wd);
	if (getcwd(buffer, PATH_MAX))
		update_envp_with_string(mshell, "PWD", buffer);
	else
		ft_printf_fd(2, ERR_NO_FILE, path->name);
	mshell->exit_code = 0;
}

/**
 * @brief Changes the current directory to the given environment variable key.
 *
 * @param mshell Pointer to the shell structure
 * @param key The environment variable key to use as the target directory.
 */
void	cd_to_key(t_shell *mshell, char *key)
{
	t_envp	*temp;

	temp = find_envp(mshell->env_list, key);
	if (!temp)
	{
		ft_printf_fd(2, ERR_CD_NO_ENVP, key);
		mshell->exit_code = 1;
	}
	else
	{
		chdir(temp->content);
		update_envp_with_string(mshell, "OLDPWD", mshell->curr_wd);
		if (getcwd(mshell->curr_wd, sizeof(mshell->curr_wd)))
			update_envp_with_string(mshell, "PWD", mshell->curr_wd);
		else
			ft_printf_fd(2, ERR_NO_FILE, temp->content);
		mshell->exit_code = 0;
	}
}

/**
 * @brief Checks the syntax of the argument
 *
 * @param mshell Pointer to the shell structure (unused).
 * @param token Pointer to the token containing the cd argument.
 * @return int 1 if the syntax is valid, 0 otherwise.
 */
int	cd_syntax(t_shell *mshell, t_token **token)
{
	char	*flag;

	(void)mshell;
	flag = (*token)->name;
	if (flag[0] == '-')
	{
		if (flag[1] == '-')
		{
			if (flag[2] == '\0')
				return (1);
			ft_printf_fd(2, ERR_CD_INVALID_OPT);
			return (0);
		}
		if (flag[1] != '\0')
		{
			ft_printf_fd(2, ERR_CD_INVALID_OPT);
			return (0);
		}
	}
	return (1);
}

/**
 * @brief Updates the environment variable in the shell with a new value.
 *
 * @param mshell Pointer to the shell structure.
 * @param key The environment variable key (e.g., "PWD" or "OLDPWD").
 * @param cwd The value to set for the environment variable.
 */
void	update_envp_with_string(t_shell *mshell, char *key, char *cwd)
{
	char	*content;
	char	*temp;
	t_token	*token;

	token = NULL;
	content = ft_strjoin(key, "=");
	temp = content;
	content = ft_strjoin(temp, cwd);
	token = ft_newtoken(content);
	update_export(mshell, &token);
	free(temp);
	free(content);
	free(token->name);
	free(token);
}
