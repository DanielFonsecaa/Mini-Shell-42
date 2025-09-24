/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:23:00 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/19 15:23:00 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Cleans up word building resources and handles syntax error messages.
 *
 * This function frees the current word and token list if needed.
 * If `res == -1`, it prints an unclosed quote error message.
 *
 * @param tk Pointer to the token list.
 * @param word Word buffer to free.
 * @param res Result code indicating error state.
 */
void	clean_words(t_token **tk, char *word, int res)
{
	if (res == -1)
		ft_putendl_fd("bash: syntax error: unclosed quote", STDERR_FILENO);
	if (word)
	{
		free(word);
		word = NULL;
	}
	if (tk && *tk)
		free_tokens(tk);
}

/**
 * @brief Extracts the value of an environment variable from the input string.
 *
 * Parses the input after the `$` character to get the variable name.
 * - If the variable is `$?`, it returns the last status code.
 * - Otherwise, it fetches the value from the environment list.
 *
 * @param bd Pointer to the token builder containing the input and environment.
 * @return A dynamically allocated string with the variable's value,
 *         or an empty string if not found or invalid.
 */
static char	*extract_variable(t_token_builder *bd)
{
	char	var[256];
	int		j;
	char	*value;

	j = 0;
	bd->pos++;
	var[0] = '\0';
	if (bd->input[bd->pos] == '?')
		return (bd->pos++, ft_itoa(*bd->last_status_code));
	if (!ft_isalpha(bd->input[bd->pos]) && bd->input[bd->pos] != '_')
		return (bd->pos++, ft_strdup(""));
	while (bd->input[bd->pos] && ((ft_isalnum(bd->input[bd->pos])
				|| bd->input[bd->pos] == '_')))
	{
		var[j] = bd->input[bd->pos];
		j++;
		bd->pos++;
	}
	var[j] = '\0';
	value = get_env_value(var, bd->envp);
	if (!value)
		return (NULL);
	return (value);
}

/**
 * @brief Appends a slice of the input string to the current partial word.
 *
 * Extracts the substring from `*start` to current `pos`, and appends
 * it to `*part`. Handles memory allocation and replacement.
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the partial word being built.
 * @param start Pointer to the index where the slice begins.
 */
static void	append_text(t_token_builder **bd, char **part, int *start)
{
	char	*tmp;
	char	*env_val;

	if (!*part)
		*part = ft_strdup("");
	tmp = ft_substr((*bd)->input, *start, (*bd)->pos - *start);
	if (!tmp)
		return ;
	env_val = ft_strjoin(*part, tmp);
	if (!env_val)
	{
		free(tmp);
		return ;
	}
	free(*part);
	free(tmp);
	*part = env_val;
}

/**
 * @brief Appends text and/or variable values to the current partial word.
 *
 * If `flag == 1`, extracts a variable and appends its value after appending
 * the plain text from `*start` to `pos`. If `flag == 0`, only
 *  the text is appended.
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the partial word being built.
 * @param start Pointer to the starting index for appending.
 * @param flag Flag controlling what to append:
 *  - 0: append only text.
 *  - 1: append text and resolve a variable.
 * @return int:
 *  - 1 on success.
 *  - 0 on memory error or invalid variable.
 */
int	append_dollar(t_token_builder **bd, char **part, int *start, int flag)
{
	char	*tmp;
	char	*env_val;

	if ((*bd)->pos > *start)
		append_text(bd, part, start);
	if (flag == 1)
	{
		env_val = extract_variable((*bd));
		if (!env_val)
		{
			if ((*bd)->del == '"')
				return (1);
			else
				return (0);
		}
		tmp = ft_strjoin(*part, env_val);
		if (!tmp)
			return (free(env_val), 0);
		free(*part);
		free(env_val);
		*part = tmp;
		*start = (*bd)->pos;
	}
	return (1);
}

/**
 * @brief Handles parsing logic when encountering a '$' character.
 *
 * Decides whether to process, skip, or ignore the dollar sign depending on
 * the context (e.g., inside quotes or invalid next characters).
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the partial word being built.
 * @param start Pointer to the starting index for the current part.
 * @return int:
 *  - STATE_CONTINUE (0): No special handling, keep going.
 *  - STATE_BREAK (1): Stop current word.
 *  - STATE_NULL (2): Variable was invalid, skip.
 */
int	check_dollar_cases(t_token_builder **bd, char **part, int *start)
{
	char	next;

	if ((*bd)->input[(*bd)->pos] == '$' && (*bd)->del != '\'')
	{
		next = (*bd)->input[(*bd)->pos + 1];
		(*bd)->startbefdol = (*bd)->input[(*bd)->pos];
		if (next == '\0' || next == ' ' || ft_strchr("\"\'\t><|=$", next))
		{
			(*bd)->pos++;
			return (STATE_CONTINUE);
		}
		if (next == '\0')
			return ((*bd)->pos++, STATE_BREAK);
		if ((*bd)->del != '\'')
		{
			if (append_dollar(bd, part, start, 1) == 0)
			{
				*start = (*bd)->pos;
				return (STATE_NULL);
			}
			return (STATE_BREAK);
		}
	}
	return (STATE_CONTINUE);
}
