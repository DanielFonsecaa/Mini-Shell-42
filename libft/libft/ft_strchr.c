/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:14:29 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 18:37:27 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	while (*s)
	{
		if (*s == (char)c)
		{
			ret = (char *)s;
			return (ret);
		}
		s++;
	}
	if (!(char)c)
	{
		ret = (char *)&s[ft_strlen(s)];
		return (ret);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	const char s[] = "teste";
	printf("%p\n", s);
	printf("%p\n", ft_strchr(s, '\0'));
	printf("%p\n", strchr(s, '\0'));
}
*/
