#include "../../inc:ludes/minishell.h"

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
		cd_no_args(mshell) // need to check
	else if (!cd_syntax(mshell, temp)) // to do
		mshell->exit_code = 2;
	else if (ft_strcmp(temp->name, "-") == 0)
		cd_old_dir("OLDPWD", mshell); //to do
	else
		change_dir(mshell, token); // to do
}

int	cd_syntax(t_shell *mshell, t_token **token)
{
	char	*flag;

	flag = (*token)->name;
	if (flag[0] == '-')
	{
		if (flag[1] == '-')
		{
			if (flag[2] == '\0')
				return (1);
			else
			{
				ft_printf_fd(2, "minishell: cd: invalid option");
				return (0);
			}
		}
		if (flag[1] != '\0')
		{
				ft_printf_fd(2, "minishell: cd: invalid option");
				return (0);
		}
	}
	return (1);	
}

void	cd_no_args(t_shell *mshell)
{
	char	buffer[PATH_MAX];
	t_envp	*temp;

	temp = find_envp(mshell->env_list, "HOME");
	if  (!temp)
	{
		ft_printf_fd(2, "minishell: cd: HOME is not set\n");
		mshell->exit_code = 1;
	}
	else
	{
		chdir(temp->content);
		update_envp_with_string(mshell, "PWD", getcwd(buffer, PATH_MAX));
		update_envp_with_string(mshell, "OLDPWD", mshell->curr_wd);
		mshell->exit_code = 0;
//		getcwd(mshell->curr_wd, sizeof(mshell->curr_wd)); needed ? uncomment : delete
	}
}

void	update_envp_with_string(t_shell *mshell, char *key, char *cwd)
{
	char *content; 
	char *temp;
	t_token *token;

	content = ft_strjoin(key, "=");
	temp = content;
	content = ft_strjoin(temp, cwd);
	ft_memset(token, 0, sizeof(t_token));
	token = ft_newtoken(content);
	update_export(mshell, &token);
	free(temp);
	free(content);
	free(token);
}
