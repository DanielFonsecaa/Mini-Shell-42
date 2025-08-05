/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:15:19 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/05 11:33:11 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <stdarg.h>

int	ft_check_fd(int fd, va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putpoint_fd(fd, va_arg(args, void *)));
	else if (c == 'd')
		return (ft_putnbr_fd(fd ,va_arg(args, int)));
	else if (c == 'i')
		return (ft_putnbr_fd(fd ,va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsint_fd(fd ,va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_puthex_small_fd(fd ,va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_puthex_big_fd(fd ,va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_putchar_fd(fd, '%'));
	return (-1);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		counter;
	va_list	args;

	va_start(args, format);
	i = 0;
	counter = 0;
	while (format[i])
	{
		if (format[i] != '%')
			counter += ft_putchar_fd(fd, format[i]);
		else
			counter += ft_check_fd(fd, args, format[++i]);
		i++;
	}
	va_end(args);
	return (counter);
}
