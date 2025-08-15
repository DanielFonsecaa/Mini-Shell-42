/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:09:22 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 10:31:36 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len ++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_get_size(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	result[len] = '\0';
	while (n > 0)
	{
		result[len -1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (result);
}
/*
#include <stdio.h>
int	main()
{
	int numbers[10] = {123, -123, 0, 42, -42, 2147483647, -2147483648};
	for (int i = 0; i < 7; i++)
	{
		char *result = ft_itoa(numbers[i]);
		printf("ft_itoa(%d) = %s\n", numbers[i], result);
		free(result);
	}
	return (0);
}
*/
