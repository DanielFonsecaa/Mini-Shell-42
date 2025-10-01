/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:38:33 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 15:38:34 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_H
# define SAFE_H

void	*safe_malloc(size_t size);
void	*safe_calloc(int nmemb, size_t size);

#endif
