/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:48:08 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/04 19:50:22 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("%d\n",ft_isalnum(97));
	printf("%d\n",ft_isalnum(68));
	printf("%d\n",ft_isalnum(75));
	printf("%d\n",ft_isalnum(48));
	printf("%d\n",ft_isalnum(50));
	printf("%d\n",ft_isalnum(55));
	printf("%d\n",ft_isalnum(4));
	printf("%d\n",ft_isalnum(6));
	return (0);
}
*/
