/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpoint_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:26:15 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/05 11:22:33 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putpoint_fd(int fd, void *ptr)
{
	unsigned long	address;
	int				j;

	address = (unsigned long)ptr;
	j = 0;
	if (!ptr)
		return (ft_putstr_fd(fd, "(nil)"));
	j += ft_putchar_fd(fd, '0');
	j += ft_putchar_fd(fd, 'x');
	j += ft_puthex_small_fd(fd, address);
	return (j);
}
