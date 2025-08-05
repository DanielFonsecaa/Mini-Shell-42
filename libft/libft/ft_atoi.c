/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:39:09 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/05 17:57:58 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
#include <stdio.h>
int	main()
{
 printf("%d\n", ft_atoi("1235"));
 printf("%d\n", ft_atoi("2147483647"));
 printf("%d\n", ft_atoi("-2147483648"));
 printf("%d\n", ft_atoi(""));
 printf("%d\n", ft_atoi("999999999999"));
 printf("%d\n", ft_atoi("-999999999999"));
 printf("%d\n", ft_atoi("(NULL)"));
 printf("%d\n", ft_atoi("\n"));
 printf("%d\n", ft_atoi("\t"));
 printf("%d\n", ft_atoi("NULL"));
}
*/
