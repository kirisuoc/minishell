/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:00:01 by ecousill          #+#    #+#             */

#include "get_next_line.h"

static size_t	ft_strlen(const char *string)
{
	size_t	length;

	length = 0;
	while (string && string[length])
		length++;
	return (length);
}

char	*free_memory(char *string)
{
	free(string);
	return (NULL);
}

char	*join_strings(char *remainder, char *new_part)
{
	size_t	remainder_len;
	size_t	newpart_len;
	char	*new_str;
	size_t	i;

	remainder_len = ft_strlen(remainder);
	newpart_len = ft_strlen(new_part);
	new_str = malloc((remainder_len + newpart_len + 1) * sizeof(char));
	if (!new_str)
		return (free_memory(remainder));
	i = 0;
	while (i < remainder_len)
	{
		new_str[i] = remainder[i];
		i++;
	}
	i = 0;
	while (i < newpart_len)
	{
		new_str[remainder_len + i] = new_part[i];
		i++;
	}
	new_str[remainder_len + i] = '\0';
	free(remainder);
	return (new_str);
}

char	*extract_line(char *remainder)
{
	char	*string;
	int		i;
	int		j;

	if (!remainder)
		return (free_memory(remainder));
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	string = malloc((i + (remainder[i] == '\n') + 1) * sizeof(char));
	if (!string)
		return (free_memory(remainder));
	j = 0;
	while (j < i)
	{
		string[j] = remainder[j];
		j++;
	}
	if (remainder[i] == '\n')
		string[i++] = '\n';
	string[i] = '\0';
	return (string);
}

char	*update_remainder(char *remainder)
{
	size_t	nl_pos;
	size_t	i;
	char	*new_remainder;

	nl_pos = 0;
	while (remainder[nl_pos] && remainder[nl_pos] != '\n')
		nl_pos++;
	if (remainder[nl_pos] == '\0')
		return (free_memory(remainder));
	new_remainder = malloc((ft_strlen(remainder) - nl_pos + 1) * sizeof(char));
	if (!new_remainder)
		return (free_memory(remainder));
	nl_pos++;
	i = 0;
	while (remainder[nl_pos + i])
	{
		new_remainder[i] = remainder[nl_pos + i];
		i++;
	}
	new_remainder[i] = '\0';
	free(remainder);
	return (new_remainder);
}
