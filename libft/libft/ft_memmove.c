/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:58:07 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/05 17:04:08 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c;
	char	*d;

	if (!n)
		return (dest);
	if (!src && !dest)
		return (NULL);
	i = -1;
	c = (char *)src;
	d = (char *)dest;
	if (dest <= src)
	{
		while (++i < n)
			d[i] = c[i];
		return (dest);
	}
	i = n;
	while (i > 0)
	{
		d[i - 1] = c[i - 1];
		i--;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char s[] = "helloo";
	char s1[] = "helloo";
	char d[] = "ihdsuahdasd";
	char d1[] = "ihdsuahdasd";
	ft_memmove(d, s, 3);
	memmove(d1, s1, 3);

	printf("%lu\n", strlen(d1));
	printf("%lu\n", strlen(d));
	printf("%s\n", d);
	printf("%s\n", d1);
}
*/
