/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:08:13 by dda-fons          #+#    #+#             */
/*   Updated: 2025/05/14 18:46:54 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	char		*newline;
	ssize_t		bytes_read;

	line = NULL;
	newline = NULL;
	while (!newline)
	{
		newline = (char *)ft_memchr_gnl(buffer, '\n', BUFFER_SIZE);
		if (!buffer[0])
		{
			bytes_read = ft_update_buffer(buffer, fd);
			if (bytes_read == 0)
				break ;
			if (bytes_read < 0)
			{
				free(line);
				return (NULL);
			}
		}
		else
			line = ft_move_buffer(buffer, ft_append(line, buffer));
	}
	return (line);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char *line;
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
	return (0);
}
//int	main()
//{
//	int i = 0;
//
//	while (i < 4)
//	{
//		printf("%s\n", get_next_line(0));
//		i++;
//	}
//    return (0);
//}
*/
