/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:26:56 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/08 19:41:58 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*end;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == 0)
		return (ft_strdup(s1));
	end = s1 + ft_strlen(s1);
	while (ft_strchr(set, *s1))
		s1++;
	if (s1 >= end)
		return (ft_substr("", 0, 0));
	while (end > s1 && ft_strchr(set, *end))
		end--;
	return (ft_substr(s1, 0, end - s1 + 1));
}
/*
void print_trimmed_string(const char *s1, const char *set)
{
    char *trimmed = ft_strtrim(s1, set);
    if (trimmed)
    {
        printf("ft_strtrim(\"%s\", \"%s\") = \"%s\"\n", s1, set, trimmed);
        free(trimmed);
	}
    else
        printf("ft_strtrim(\"%s\", \"%s\") returned NULL\n", s1, set);
}

int main()
{
    print_trimmed_string("  Hello, World!  ", " ");
    print_trimmed_string("**Hello, World!**", "*");
    print_trimmed_string("Hello, World!", "#");
    print_trimmed_string("", " ");
    print_trimmed_string("###Hello", "#");
    print_trimmed_string("Hello###", "#");
    print_trimmed_string("####", "#");
    print_trimmed_string("", "");
    print_trimmed_string("abcdef", "xyz");
    print_trimmed_string("xxabcdefxx", "x");
    print_trimmed_string("xxabcxx", "x");
    return 0;
}
*/
