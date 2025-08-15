/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:46:37 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 17:10:46 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*temp;

	i = 0;
	c1 = (unsigned char *)s;
	while (i < n)
	{
		if (c1[i] == (unsigned char)c)
		{
			temp = (unsigned char *)&c1[i];
			return (temp);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	const void *str = "daniel";
	int c = 'x';
	char *s = ft_memchr(str, c, 6);
	printf("%s\n", s);
}
*/
