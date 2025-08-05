/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:05:54 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 12:31:11 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
void	ft_change(unsigned int i, char * str)
{
	*str += i;
}
int	main()
{
	char *result = "hello";
	ft_striteri(result, ft_change);
	printf("%s\n", result);
	result = "";
	ft_striteri(result, ft_change);
	printf("%s\n", result);
	result = "a";
	ft_striteri(result, ft_change);
	printf("%s\n", result);
	result = "!#$";
	ft_striteri(result, ft_change);
	printf("%s\n", result);
}*/
