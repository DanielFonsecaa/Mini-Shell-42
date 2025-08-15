/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:03:10 by dda-fons          #+#    #+#             */
/*   Updated: 2025/05/14 18:46:43 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlcat_gnl(char *dst, char *src, size_t size);
void	*ft_memchr_gnl(void *s, int c, size_t n);
char	*ft_append(char *old, char *buffer);
int		ft_update_buffer(char *buffer, int fd);
char	*ft_move_buffer(char *buffer, char *line);

#endif
