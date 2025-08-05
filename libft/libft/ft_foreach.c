/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:36:36 by dda-fons          #+#    #+#             */
/*   Updated: 2025/05/24 15:42:22 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_foreach(char **str, int (*func)(char *))
{
	int	i;
	int	*result;

	i = 0;
	while (str[i])
		i++;
	result = malloc(sizeof(int) * i);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = func(str[i]);
		i++;
	}
	return (result);
}
