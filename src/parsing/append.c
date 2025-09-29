#include "../../includes/minishell.h"

// Extracts variable and appends its value to str
int	append_envar_val(t_shell *ms, t_token **tok, char **str, int start)
{
	int		len;
	char	*variable;
	char	*new_content;
	t_envp	*node;

	len = 0;
	while ((*tok)->name[start + len])
	{
		if (!(ft_isalnum((*tok)->name[start + len])
				|| (*tok)->name[start + len] == '_'))
			break ;
		len++;
	}
	variable = ft_substr((*tok)->name, start, len);
	node = find_envp(ms->env_list, variable);
	if (node)
		new_content = node->content;
	else
		new_content = "";
	*str = ft_strjoin_free(*str, new_content);
	free(variable);
	return (start + len);
}

char	*append_content(t_shell *mshell, t_token **token, char *str, int *i)
{
	int	start;

	start = *i + 1;
	if (handle_special_var_case(token, &str, i, start))
		return (str);
	*i = append_envar_val(mshell, token, &str, start);
	return (str);
}

char	*append_letter(t_token **token, char *new_str, int *i)
{
	char	tmp[2];
	char	quote_char;

	if (((*token)->name[*i] == '"' || (*token)->name[*i] == '\''))
	{
		quote_char = (*token)->name[*i];
		(*i)++;
		while ((*token)->name[*i] && (*token)->name[*i] != quote_char)
		{
			tmp[0] = (*token)->name[*i];
			tmp[1] = 0;
			new_str = ft_strjoin_free(new_str, tmp);
			(*i)++;
		}
		if ((*token)->name[*i] == quote_char)
			(*i)++;
	}
	else
	{
		tmp[0] = (*token)->name[*i];
		tmp[1] = 0;
		new_str = ft_strjoin_free(new_str, tmp);
		(*i)++;
	}
	return (new_str);
}

char	*append_letter_unquoted(t_token *token, char *new_str, int *i)
{
	char	tmp[2];

	tmp[0] = token->name[*i];
	tmp[1] = 0;
	new_str = ft_strjoin_free(new_str, tmp);
	(*i)++;
	return (new_str);
}
