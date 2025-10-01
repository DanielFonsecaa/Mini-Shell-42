/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:15:54 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:19:57 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
			{
				i++;
				quote = 0;
			}
			continue ;
		}
		if (!quote && (ft_iswhite_space(s[i]) || is_meta_char(s[i])))
			break ;
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
	char	c;

	*j = 0;
	c = 0;
	if (is_meta_char(rd_l[i + *j]))
		c = rd_l[i + *j];
	while (rd_l[i + *j] && is_meta_char(rd_l[i + *j]) && c == rd_l[i + *j])
		(*j)++;
	if (*j && is_meta_char(rd_l[i + *j - 1]))
		ft_first_token(token, rd_l + i, *j);
	return (i + *j);
}

char	*extract_cmd_token(char *rd_l, int *i)
{
	int		start;
	int		in_quote;
	char	quote_char;
	int		len;

	init_values(&len, &start, &in_quote, i);
	quote_char = 0;
	while (rd_l[(*i)])
	{
		if (!in_quote && (rd_l[*i] == '\'' || rd_l[*i] == '"'))
		{
			in_quote = 1;
			quote_char = rd_l[*i];
		}
		else if (in_quote && rd_l[*i] == quote_char)
			in_quote = 0;
		else if (!in_quote && (ft_iswhite_space(rd_l[*i])
				|| is_meta_char(rd_l[*i])))
			break ;
		else
			len++;
		(*i)++;
	}
	return (get_cmd_token(rd_l, start, len, quote_char));
}

char	*get_cmd_token(char *rd_l, int start, int len, char quote_char)
{
	char	*name;
	int		i;
	int		in_quote;

	in_quote = 0;
	i = 0;
	if (len == 1)
		return (ft_substr(rd_l, start, 3));
	name = safe_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		if (handle_quote(rd_l, &start, &in_quote, &quote_char))
			continue ;
		name[i++] = rd_l[start++];
	}
	return (name);
}
