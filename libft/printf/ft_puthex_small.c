/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_small.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:30:20 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 13:38:08 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_small(unsigned long n)
{
	int		j;
	char	*hex;

	hex = "0123456789abcdef";
	j = 0;
	if (n >= 16)
	{
		j += ft_puthex_small(n / 16);
	}
	j += ft_putchar(hex[n % 16]);
	return (j);
}
