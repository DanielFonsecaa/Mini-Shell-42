/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:14 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/05 11:36:26 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <unistd.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_putnbr_fd(int fd, int n);
int	ft_puthex_small_fd(int fd, unsigned long n);
int	ft_puthex_big_fd(int fd, unsigned long n);
int	ft_putunsint_fd(int fd, unsigned int n);
int	ft_putchar_fd(int fd, char c);
int	ft_putstr_fd(int fd, char *s);
int	ft_putpoint_fd(int fd, void *ptr);

#endif
