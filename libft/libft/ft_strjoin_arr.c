/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:30 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/08 14:35:12 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_arr(char **s2)
{
	char	*ret;
	size_t	size;
	int     i;
	int     j;

	if (!s2 || !*s2)
		return (NULL);
	i = -1;
	size = 0;
	while (s2[++i])
		size += ft_strlen(s2[i]);
	size++;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = -1;
	size = 0;
	while (s2[++i])
	{
		j = -1;
		while (s2[i][++j])
			ret[size++] = s2[i][j];
	}
	ret[size] = '\0';
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
