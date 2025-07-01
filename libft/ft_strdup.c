/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:49 by ecousill          #+#    #+#             */
/*   Updated: 2025/07/01 20:52:00 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	s_length;
	char	*start_cpy;

	s_length = ft_strlen(s);
	cpy = malloc(s_length + 1);
	if (cpy == NULL)
		return (NULL);
	start_cpy = cpy;
	while (*s)
		*cpy++ = *s++;
	*cpy = '\0';
	return (start_cpy);
}
