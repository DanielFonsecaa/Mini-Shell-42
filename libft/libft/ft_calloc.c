/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:43:50 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/07 20:55:09 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	m;

	m = size * nmemb;
	ret = malloc(m);
	if (!ret)
		return (NULL);
	ft_bzero(ret, m);
	return (ret);
}
/*
#include <stdio.h>
int	main()
{
	void *ptr = ft_calloc(5, sizeof(int));
	if (ptr)
	{
		for (size_t i = 0; i < 5 * sizeof(int); i++)
		{
			if (((unsigned char *)ptr)[i] != 0)
			{
				printf("FAILED");
				free(ptr);
				return (0);
			}
		}
			printf("SUCCESS");
	}
	else 
		printf("FAILED");
	free(ptr);
}
*/
