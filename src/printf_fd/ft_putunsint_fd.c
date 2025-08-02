/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:40 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/30 13:46:03 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsint_fd(int fd, unsigned int n)
{
	long	i;
	int		j;

	j = 0;
	i = n;
	if (i < 0)
	{
		i *= -1;
		j += ft_putchar_fd(fd, '-');
	}
	if (i >= 10)
		j += ft_putunsint_fd(fd, i / 10);
	j += ft_putchar_f(fd, (i % 10) + '0');
	return (j);
}
/*
int	main()
{
	ft_putnbr_fd(1235, 2);
}
*/
