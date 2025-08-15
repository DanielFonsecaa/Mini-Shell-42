/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:06:30 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/08 10:06:50 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (i <= start)
		return (ft_strdup(""));
	i -= start;
	if (len > i)
		len = i;
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
/*
#include <stdio.h>
int	main()
{
	char *str = "Hello, World!";
	char *result;

    result = ft_substr(str, 7, 5);
	printf("%s\n", result);
	free(result);

    result = ft_substr(str, 0, 5);
    printf("%s\n", result);
    free(result);

    result = ft_substr(str, 0, 50);
    printf("%s\n", result);
    free(result);

    result = ft_substr(str, 20, 5);
    printf("%s\n", result);
    free(result);

    result = ft_substr(str, ft_strlen(str), 5);
    printf("%s\n", result);
    free(result);

    result = ft_substr(NULL, 0, 5);
    printf("%s\n", result);
    free(result);
	return 0;
}
*/
