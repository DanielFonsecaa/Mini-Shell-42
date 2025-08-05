/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:32:37 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/05 11:42:14 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
int	main()
{
	const char *c = "daniel";
	const char *c1 = "";
	const char *c2 = "d";
	const char *c3 = "da";
	const char *c4 = " ";
	const char *c5 = "1";
	printf("%zu\n", ft_strlen(c));
	printf("%zu\n", ft_strlen(c1));
	printf("%zu\n", ft_strlen(c2));
	printf("%zu\n", ft_strlen(c3));
	printf("%zu\n", ft_strlen(c4));
	printf("%zu\n", ft_strlen(c5));
}
*/
