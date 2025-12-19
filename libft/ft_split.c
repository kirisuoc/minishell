/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:24:49 by erikcousill       #+#    #+#             */
/*   Updated: 2025/12/19 13:54:04 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	in_word;
	int	num_strings;

	num_strings = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			num_strings++;
			in_word = 1;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (num_strings);
}

static char	*allocate_word(char const *start, int len)
{
	int		i;
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	get_word_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**push_words_in_array(char **array, char const *s, char c, int i)
{
	const char	*start;
	int			len;

	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			len = get_word_length(s, c);
			array[i] = allocate_word(start, len);
			if (!array[i])
			{
				while (i >= 0)
					free((array[i--]));
				free(array);
				return (NULL);
			}
			i++;
			s += len;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;
	int		i;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	array = malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	return (push_words_in_array(array, s, c, i));
}

/* int	main(void)
{
	char *string = NULL;
	char	**matrix = ft_split(string, '/');

	printf("%s, %s, %s", matrix[0], matrix[1], matrix[2]);
	return (0);
} */
