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

int	ft_putunsint(unsigned int n)
{
	long	i;
	int		j;

	j = 0;
	i = n;
	if (i < 0)
	{
		i *= -1;
		j += ft_putchar('-');
	}
	if (i >= 10)
		j += ft_putunsint(i / 10);
	j += ft_putchar((i % 10) + '0');
	return (j);
}
/*
int	main()
{
	ft_putnbr_fd(1235, 2);
}
*/
