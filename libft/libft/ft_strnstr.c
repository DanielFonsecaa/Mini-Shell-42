/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:19:47 by dda-fons          #+#    #+#             */
/*   Updated: 2025/09/24 19:31:45 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big)
		return (NULL);
	i = -1;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	if (len == 0)
		return (NULL);
	while (big[++i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len && little[j])
			j ++;
		if (!little[j])
			return ((char *)&big[i]);
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
