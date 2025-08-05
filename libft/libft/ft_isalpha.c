/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:37:12 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/04 16:00:33 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("result -\"%d\"\n", ft_isalpha('0'));
	printf("result -\"%d\"\n", ft_isalpha('A'));
	printf("result -\"%d\"\n", ft_isalpha('z'));
	printf("result -\"%d\"\n", ft_isalpha(' '));
	printf("result -\"%d\"\n", ft_isalpha('!'));
	printf("result -\"%d\"\n", ft_isalpha('\n'));
	printf("result -\"%d\"\n", ft_isalpha('\t'));
	printf("result -\"%d\"\n", ft_isalpha('\0'));
	
	return (0);
}
*/
