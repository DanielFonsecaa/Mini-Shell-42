/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:14 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:16 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr(int n);
int	ft_puthex_small(unsigned long n);
int	ft_puthex_big(unsigned long n);
int	ft_putunsint(unsigned int n);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putpoint(void *ptr);

#endif
