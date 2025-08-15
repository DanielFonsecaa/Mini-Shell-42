/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:51:08 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/05 15:57:45 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c;
	char	*d;

	if (!n)
		return (dest);
	if (!src && !dest)
		return (NULL);
	i = 0;
	c = (char *)src;
	d = (char *)dest;
	while (i < n)
	{
		d[i] = c[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char s[99] = "hello asdasdasdas";
	char d[99];
	char d1[99];
	ft_memcpy(d, s, 4);
	memcpy(d1, s, 4);

	printf("%lu\n", strlen(d));
	printf("%lu\n", strlen(d1));
	printf("%s\n", d);
	printf("%s\n", d1);
}
*/
