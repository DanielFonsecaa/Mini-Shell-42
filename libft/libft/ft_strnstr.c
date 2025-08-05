/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:19:47 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 15:40:45 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	if (little[0] == '\0')
	{
		temp = (char *)&big[0];
		return (temp);
	}
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len && little[j])
			j ++;
		if (!little[j])
		{
			temp = (char *)&big[i];
			return (temp);
		}
		i ++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char	c[] = "alex e julio feios";
	const char	d[] = "ei";

	printf("%s\n", ft_strnstr(c, d, 17));
}
*/
