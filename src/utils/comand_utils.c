#include "../../includes/minishell.h"

void    set_mshell_commands(t_shell *mshell, t_token **token)
{
	t_token *temp;
	char    **commands;
	int     i;

	i = 0;
	temp = *token;
	while (temp)
	{
		if (temp->type == CMD)
			i++;
		temp = temp->next;
	}
	commands = safe_calloc(i + 1, sizeof(char *));
	temp = *token;
	i = 0;
	while (temp)
	{
		if (temp->type == CMD)
			commands[i++] = ft_strdup(temp->name);
		temp = temp->next;
	}
	mshell->commands = commands;
	mshell->num_commands = i;
}