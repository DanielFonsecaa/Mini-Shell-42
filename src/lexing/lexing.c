/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipinhei <mipinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:24 by mipinhei          #+#    #+#             */
/*   Updated: 2025/10/01 15:17:25 by mipinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Tokenizes a command line string into a linked list of tokens
 *
 * @param rd_l The input command line string to tokenize
 * @param token Pointer to the token list where new tokens will be added
 */
int	tokenize(char *rd_l, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rd_l[i])
	{
		i = skip_whitespace(rd_l, i);
		j = next_token_len(rd_l + i);
		if (j > 0 && !is_meta_char(rd_l[i]))
			ft_first_token(token, rd_l + i, j);
		i += j;
		if (rd_l[i] == '|' && rd_l[i + 1] == '|')
			return (ft_printf_fd(2, ERR_PIPELINE), 0);
		i = handle_meta(rd_l, token, i, &j);
		if (j > 2)
			return (ft_printf_fd(2, ERR_SYNTAX), 0);
		if (rd_l[i] && rd_l[i - 1] == '|')
		{
			i = skip_whitespace(rd_l, i);
			if (!is_meta_char(rd_l[i]))
				add_command_token(rd_l, token, &i);
		}
	}
	return (1);
}

/**
 * @brief Creates and adds the first token to the token list from a given line
 * 
 * @param token Double pointer to the list where the new token
 * @param line Source string from which to extract the token content
 * @param size Number of characters to extract from the beginning of line
 */
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

/**
 * @brief Sets the token type for each token in a linked list
 * 			based on token content and position
 * 
 * @param token Double pointer to the first token in the linked list
 */

void	set_t_type(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		if (ft_strcmp(temp->name, "<<") == 0 && !temp->has_quote)
			temp->type = HERE;
		else if (ft_strcmp(">>", temp->name) == 0 && !temp->has_quote)
			temp->type = APPEND;
		else if (ft_strcmp(">", temp->name) == 0 && !temp->has_quote)
			temp->type = OUTFILE;
		else if (ft_strcmp("<", temp->name) == 0 && !temp->has_quote)
			temp->type = INFILE;
		else if (temp->prev && temp->prev->type == HERE)
			temp->type = LIMITER;
		else if (ft_strcmp("|", temp->name) == 0 && !temp->has_quote)
			temp->type = PIPE;
		else
			set_t_arg(&temp);
		temp = temp->next;
	}
	temp = *token;
}

void	set_command(t_token **token)
{
	t_token	*temp;
	bool	flag;

	flag = false;
	temp = *token;
	while (temp)
	{
		if (temp->type == CMD)
		{
			flag = true;
			temp = temp->next;
			continue ;
		}
		if (!flag && temp->type == ARG)
		{
			temp->type = CMD;
			flag = true;
		}
		else if (temp->type == PIPE)
			flag = false;
		temp = temp->next;
	}
}

/**
 * @brief Updates token types to identify file arguments
 * 			following redirection operators
 * 
 * @param token Double pointer to the head of the token linked list
 */
void	type_file(t_token **token)
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
