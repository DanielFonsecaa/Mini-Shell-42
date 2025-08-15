/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:00:34 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/04 20:02:15 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("%d\n",ft_isprint(0));
	printf("%d\n",ft_isprint(127));
	printf("%d\n",ft_isprint(75));
	printf("%d\n",ft_isprint(126));
	printf("%d\n",ft_isprint(32));
	return (0);
}
*/
