/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:34 by dda-fons          #+#    #+#             */
/*   Updated: 2025/05/14 18:47:37 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat_gnl(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_dst = 0;
	len_src = 0;
	while (dst[len_dst])
		len_dst++;
	while (src[len_src])
		len_src++;
	if (size == 0)
		return (len_src);
	if (len_dst >= size)
		return (len_src + size);
	i = 0;
	while (i < (size - 1 - len_dst) && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

char	*ft_append(char *old, char *buffer)
{
	char	*new;
	size_t	len_old;
	size_t	i;
	size_t	len_nl;

	i = 0;
	len_old = 0;
	len_nl = 0;
	while (old && old[len_old])
		len_old++;
	while (buffer[len_nl] && buffer[len_nl] != '\n')
		len_nl++;
	len_nl += (buffer[len_nl] == '\n');
	new = malloc(sizeof(char) * (len_old + len_nl + 1));
	if (!new)
		return (free(old), NULL);
	while (i < len_nl)
		new[i++] = '\0';
	if (old)
	{
		ft_strlcat_gnl(new, old, len_old + 1);
		free(old);
	}
	ft_strlcat_gnl(new, buffer, len_old + len_nl + 1);
	return (new);
}

void	*ft_memchr_gnl(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*temp;

	i = 0;
	c1 = (unsigned char *)s;
	while (i < n)
	{
		if (c1[i] == (unsigned char)c)
		{
			temp = (unsigned char *)&c1[i];
			return (temp);
		}
		i++;
	}
	return (0);
}

int	ft_update_buffer(char *buffer, int fd)
{
	ssize_t	bytes_read;
	size_t	i;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	i = bytes_read;
	if (bytes_read <= 0)
		return (bytes_read);
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
	return (bytes_read);
}

char	*ft_move_buffer(char *buffer, char *line)
{
	size_t	j;
	size_t	len_nl;

	len_nl = 0;
	j = 0;
	while (buffer[len_nl] && buffer[len_nl] != '\n')
		len_nl++;
	if (buffer[len_nl] == '\n')
		len_nl++;
	while (buffer[len_nl])
		buffer[j++] = buffer[len_nl++];
	while (j < BUFFER_SIZE)
		buffer[j++] = '\0';
	return (line);
}
