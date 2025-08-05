/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:35:14 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 12:05:06 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*result;
	unsigned int		len;
	unsigned int		i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char example_function(unsigned int i, char c) {

	(void)i;
    return (c + 1);
}

#include <stdio.h>
int main()
{
    char *result;

    result = ft_strmapi("hello", example_function);
    printf("%s\n", result); // Expected: "hfnos"
    free(result);

    result = ft_strmapi("", example_function);
    printf("%s\n", result);
	free(result);

    result = ft_strmapi("a", example_function);
    printf("%s\n", result);
	free(result);

    result = ft_strmapi("!@#", example_function);
    printf("%s\n", result);
    free(result);
}
*/
