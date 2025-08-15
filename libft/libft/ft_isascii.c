/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:54:52 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/04 19:56:49 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("%d\n",ft_isascii(97));
	printf("%d\n",ft_isascii(68));
	printf("%d\n",ft_isascii(75));
	printf("%d\n",ft_isascii(200));
	printf("%d\n",ft_isascii(128));
	return (0);
}*/
