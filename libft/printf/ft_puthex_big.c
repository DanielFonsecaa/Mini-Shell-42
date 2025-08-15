/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_big.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:36 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/30 14:21:41 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_big(unsigned long n)
{
	int		j;
	char	*hex;

	hex = "0123456789ABCDEF";
	j = 0;
	if (n >= 16)
	{
		j += ft_puthex_big(n / 16);
	}
	j += ft_putchar(hex[n % 16]);
	return (j);
}
