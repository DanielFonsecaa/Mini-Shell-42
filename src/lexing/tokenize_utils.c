#include "../../includes/minishell.h"

int skip_whitespace(char *str, int i)
{
	while (ft_iswhite_space(str[i]))
		i++;
	return i;
}

int tokenize_arg(char *rd_l, int i, int *j)
{
	*j = 0;
	if (rd_l[i] == '\'' || rd_l[i] == '"')
		skip_inside_quotes(rd_l + i, j, rd_l[i]);
	else
		while (rd_l[i + *j] && !ft_iswhite_space(rd_l[i + *j])
		       && !is_meta_char(rd_l[i + *j]) && (rd_l[i + *j] != '\'' && rd_l[i + *j] != '"'))
			(*j)++;
	return i + *j;
}

void add_command_token(char *rd_l, t_token **token, int *i)
{
	char *cmd_token;
	cmd_token = extract_cmd_token(rd_l, i);
	ft_first_token(token, cmd_token, (int)ft_strlen(cmd_token));
	free(cmd_token);
}

int handle_meta(char *rd_l, t_token **token, int i, int *j)
{
	while (is_meta_char(rd_l[i + *j]))
		(*j)++;
	if (*j && is_meta_char(rd_l[i + *j - 1]))
		ft_first_token(token, rd_l + i, *j);
	return i + *j;
}