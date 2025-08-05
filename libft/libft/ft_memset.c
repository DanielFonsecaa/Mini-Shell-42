/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:42:40 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/05 12:30:34 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ch;

	ch = (char *)s;
	i = 0;
	while (i < n)
	{
		ch[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char s[99] = "hello asdasdasdas";
	char s1[99] = "hello asdasdasdas";
	ft_memset(s, 'A', 4);
	memset(s1, 'A', 4);
	printf("%s\n", s);
	printf("%s\n", s1);
}
*/
