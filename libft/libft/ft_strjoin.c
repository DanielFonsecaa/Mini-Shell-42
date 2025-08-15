/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:30 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/08 14:35:12 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, size);
	ft_strlcat(ret, s2, size);
	return (ret);
}
/*
#include <stdio.h>
int	main()
{
  char *result;

    result = ft_strjoin("Hello, ", "World!");
    printf("%s and expected 'Hello, World!'\n", result);
    free(result);

    result = ft_strjoin(NULL, NULL);
    printf("%s expected NULL\n", result);
	free(result);

	result = ft_strjoin("", "World!");
    printf("%s expected World!\n", result);
	free(result);

    result = ft_strjoin("Hello, ", "");
    printf("%s expected Hello, \n", result);
    free(result);

    result = ft_strjoin("", "");
    printf("\"%s\" expected \"\"\n", result);
    free(result);
}*/
