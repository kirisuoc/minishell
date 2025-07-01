/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:59:41 by ecousill          #+#    #+#             */

#include "get_next_line.h"

static int	has_newline(char *string)
{
	while (string && *string != '\0')
	{
		if (*string == '\n')
			return (1);
		string++;
	}
	return (0);
}

static char	*problem_reading(char *buffer, char **remainder)
{
	char	*line;

	free(buffer);
	if (*remainder)
	{
		line = extract_line(*remainder);
		*remainder = update_remainder(*remainder);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remainder[MAX_FD];
	int			bytes_read;
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!has_newline(remainder[fd]))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (problem_reading(buffer, &remainder[fd]));
		buffer[bytes_read] = '\0';
		remainder[fd] = join_strings(remainder[fd], buffer);
		if (!remainder[fd])
			return (free_memory(remainder[fd]));
	}
	free(buffer);
	line = extract_line(remainder[fd]);
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
