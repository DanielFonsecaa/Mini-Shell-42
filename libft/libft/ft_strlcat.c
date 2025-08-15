/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:18:45 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 18:07:38 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!dst && !size)
		return (0);
	len = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (len >= size)
		return (ft_strlen(src) + size);
	while (i < (size - 1 - len) && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
/*
#include <string.h>
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	const char *c = "danl";
	char d[20] = "eu sou o ";
	char d2[20] = "eu sou o ";
	printf("%zu\n", ft_strlcat(d, c, 20));
	printf("%zu\n", strlcat(d2, c, 20));
}
*/
