#include "../../includes/minishell.h"

int	skip_whitespace(char *str, int i)
{
	while (str[i] && ft_iswhite_space(str[i]))
		i++;
	return (i);
}

int	next_token_len(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '"' || s[i] == '\''))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
			{
				i++;
				quote = 0;
			}
		}
		if (!quote && (ft_iswhite_space(s[i]) || is_meta_char(s[i])))
			break ;
		else if (s[i])
			i++;
	}
	return (i);
}

void	add_command_token(char *rd_l, t_token **token, int *i)
{
	char	*cmd_token;

	cmd_token = extract_cmd_token(rd_l, i);
	ft_first_token(token, cmd_token, (int)ft_strlen(cmd_token));
	free(cmd_token);
}

int	handle_meta(char *rd_l, t_token **token, int i, int *j)
{
	while (rd_l[i + *j] && is_meta_char(rd_l[i + *j]))
		(*j)++;
	if (*j && is_meta_char(rd_l[i + *j - 1]))
		ft_first_token(token, rd_l + i, *j);
	return (i + *j);
}
