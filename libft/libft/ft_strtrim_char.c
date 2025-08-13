/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:26:56 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/13 15:14:27 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_char(char const *s1, char c)
{
	const char	*end;

	if (!s1 || !c)
		return (NULL);
	if (s1[0] == 0)
		return (ft_strdup(s1));
	end = s1 + ft_strlen(s1);
	while (ft_strchr(&c, *s1))
		s1++;
	if (s1 >= end)
		return (ft_substr("", 0, 0));
	while (end > s1 && ft_strchr(&c, *end))
		end--;
	return (ft_substr(s1, 0, end - s1 + 1));
}
