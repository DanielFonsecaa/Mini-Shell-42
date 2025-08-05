/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:40:17 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 18:56:20 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = 0;
	temp = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			temp = (char *)&s[i];
		i++;
	}
	if (!(char)c)
		return ((char *)&s[i]);
	return (temp);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	const char s[] = "teste";
	char *s1 = ft_strrchr(s, 1024);
	char *s2 = strrchr(s, 1024);
	printf("%p\n", s1);
	printf("%p\n", s2);
}
*/
