/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_small_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:30:20 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/05 11:22:20 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_puthex_small_fd(int fd, unsigned long n)
{
	int		j;
	char	*hex;

	hex = "0123456789abcdef";
	j = 0;
	if (n >= 16)
	{
		j += ft_puthex_small_fd(fd, n / 16);
	}
	j += ft_putchar_fd(fd, hex[n % 16]);
	return (j);
}
