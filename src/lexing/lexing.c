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
		while (rd_l[i + j] && !ft_iswhite_space(rd_l[i + j])
			&& !is_meta_char(rd_l[i + j]))
			j++;
		if ((rd_l[i] || rd_l[i + j]) && !is_meta_char(rd_l[i]))
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

static void	set_t_type(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		ft_printf("value %s\n", temp->name);
		if (ft_strcmp(temp->name, "<<") == 0)
				temp->type = HERE;
		else if (ft_strcmp(">>", temp->name) == 0)
			temp->type = APPEND;
		else if (ft_strcmp(">", temp->name) == 0)
			temp->type = OUTFILE;
		else if (ft_strcmp("<", temp->name) == 0)
			temp->type = INFILE;
		else if (temp->prev == NULL || (temp->prev->type == PIPE
				&& ft_strcmp(temp->name, "|") != 0))
			temp->type = CMD;
		else if (ft_strcmp("|", temp->name) == 0)
			temp->type = PIPE;
		else
			temp->type = ARG;
		temp = temp->next;
	}
}

static void	type_file(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		if (temp->prev)
		{
			if ((temp->prev->type == APPEND || temp->prev->type == INFILE
					|| temp->prev->type == OUTFILE) && temp->type == ARG)
				temp->type = TFILE;
		}
		temp = temp->next;
	}
}

void	split_rdline(t_shell *mshell, t_token **token)
{
	tokenize(mshell->rd_l, token);
	mshell->tokens_size = token_list_size(*token);
	set_t_type(token);
	type_file(token);
	print_list(token);
	pipe_count(mshell, token);
	ft_printf("token size --%i\n num pipes --%i\n", mshell->tokens_size, mshell->num_pipes);
}
