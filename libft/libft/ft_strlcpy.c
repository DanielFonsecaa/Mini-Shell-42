/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:56:45 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 16:35:39 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len ++;
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char src[] = "daniel";
	char dest[12];
	printf("%lu\n", ft_strlcpy(dest, src, 6));
	char src1[] = "daniel1234";
	char dest1[12];
	printf("%lu\n", ft_strlcpy(dest1, src1, 14));
}
*/
