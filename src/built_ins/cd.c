#include "../../includes/minishell.h"

void	handle_cd(t_shell *mshell, t_token **token)
{
	t_token	*temp;

	temp = (*token)->next;
	if (token_list_size(temp) > 1)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
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

void	change_dir(t_shell *mshell, t_token **token)
{
	char	buffer[PATH_MAX];
	t_token	*path;

	path = *token;
	if (chdir(path->name) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path->name);
		mshell->exit_code = 1;
		return ;
	}
	update_envp_with_string(mshell, "PWD", getcwd(buffer, PATH_MAX));
	update_envp_with_string(mshell, "OLDPWD", mshell->curr_wd);
	mshell->exit_code = 0;
}

void	cd_to_key(t_shell *mshell, char *key)
{
	char	buffer[PATH_MAX];
	t_envp	*temp;

	temp = find_envp(mshell->env_list, key);
	if  (!temp)
	{
		ft_printf_fd(2, "minishell: cd: %s is not set\n", key);
		mshell->exit_code = 1;
	}
	else
	{
		chdir(temp->content);
		update_envp_with_string(mshell, "PWD", getcwd(buffer, PATH_MAX));
		update_envp_with_string(mshell, "OLDPWD", mshell->curr_wd);
		mshell->exit_code = 0;
		getcwd(mshell->curr_wd, sizeof(mshell->curr_wd));// needed ? uncomment : delete
	}
}

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
			ft_printf_fd(2, "minishell: cd: invalid option\n");
			return (0);
		}
		if (flag[1] != '\0')
		{
			ft_printf_fd(2, "minishell: cd: invalid option\n");
			return (0);
		}
	}
	return (1);
}

void	update_envp_with_string(t_shell *mshell, char *key, char *cwd)
{
	char *content; 
	char *temp;
	t_token *token;

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
