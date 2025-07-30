#include "../../includes/minishell.h"

void	ft_first_token(t_token **token, char *line, int size)
{
	char	*str;
	int		i;

	str = safe_malloc(size + 1);
	i = 0;
	str[size] = '\0';
	while (i < size)
	{
		str[i] = line[i];
		i++;
	}
	token_addback(token, ft_newtoken(str));
	free(str);
}

void	tokenize(char *rd_l, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	while (rd_l[i])
	{
		while (ft_iswhite_space(rd_l[i]))
			i++;
		j = 0;
		while (rd_l[i + j] && !ft_iswhite_space(rd_l[i + j]) && !is_meta_char(rd_l[i + j]))
			j++;
		ft_first_token(token, rd_l + i, j);
		i += j;
		j = 0;
		while (is_meta_char(rd_l[i + j]))
			j++;
		if (is_meta_char(rd_l[i + j - 1]))
			ft_first_token(token, rd_l + i, j);
		i += j;
	}
}

void	split_rdline(t_shell *mshell, t_token **token)
{
//	mshell->tokens_size = count_tokens(mshell->rd_l);
//	mshell->cmd_line = safe_calloc(mshell->tokens_size, sizeof(char *));
	tokenize(mshell->rd_l, token);
	ft_printf("%i\n", mshell->tokens_size);
}

/*static int	count_tokens(char *rd_l)
{
	int	count;
	int	i;
	count = 0;
	i = -1;
	while (rd_l[++i])
	{
			if(!increment_token(rd_l[i - 1]) && increment_token(rd_l[i]))
			{
				count++;
			}
			while (ft_isspace(rd_l[i]))
				i++;
			if (is_meta_char(*rd_l))
				count++;
	}
	if (!ft_isspace(rd_l[i - 1]))
		count++;
	return (count);
}*/
