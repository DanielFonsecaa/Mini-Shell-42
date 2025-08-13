/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:04:38 by mipinhei          #+#    #+#             */
/*   Updated: 2025/08/13 12:24:21 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	verify_overflow(int sign, int digit, long long *result)
{
	if (sign == 1 && (*result > (LLONG_MAX - digit) / 10))
		return (0);
	if (sign == -1 && (*result < (LLONG_MIN + digit) / 10))
		return (0);
	*result = *result * 10 + digit;
	return (1);
}

int	ft_atoll(const char *nptr, long long *value)
{
	int			i;
	int			digit;
	int			sign;
	long long	result;

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
		digit = nptr[i] - '0';
		if (!verify_overflow(sign, digit, &result))
			return (0);
		i++;
	}
	*value = result * sign;
	return (1);
}
