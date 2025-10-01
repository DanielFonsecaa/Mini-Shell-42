/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:41:16 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:41:17 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Safely allocates memory using malloc with error checking
 * 
 * @param size The number of bytes to allocate
 * @return void* Pointer to the allocated memory block, or NULL
 * 			if allocation fails
 */
void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	return (ret);
}

/**
 * @brief Safely allocates and initializes memory using ft_calloc
 * 		with error handling
 * 
 * @param nmemb Number of elements to allocate
 * @param size Size in bytes of each element
 * @return void* Pointer to the allocated memory, or NULL
 * 			if allocation fails
 */
void	*safe_calloc(int nmemb, size_t size)
{
	void	*ret;

	ret = ft_calloc(nmemb, size);
	if (!ret)
		return (NULL);
	return (ret);
}
