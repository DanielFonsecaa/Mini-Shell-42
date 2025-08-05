/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:22:41 by dda-fons          #+#    #+#             */
/*   Updated: 2025/08/05 11:22:43 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_putstr_fd(fd, "(null)"));
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
/*
int	main()
{
	ft_putstr_fd("daniel", 2);
}
*/
