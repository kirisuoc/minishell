#include "minishell.h"

static int	count_words(char const *s)
{
	int	in_word;
	int	num_strings;

	num_strings = 0;
	in_word = 0;
	while (*s)
	{
		if (!is_whitespace(*s) && in_word == 0)
		{
			num_strings++;
			in_word = 1;
		}
		else if (is_whitespace(*s))
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

static int	get_word_length(char const *s)
{
	int	len;

	len = 0;
	while (*s && !is_whitespace(*s))
	{
		len++;
		s++;
	}
	return (len);
}

static char	**push_words_in_array(char **array, char const *s, int i)
{
	const char	*start;
	int			len;

	while (*s)
	{
		while (is_whitespace(*s))
			s++;
		if (*s)
		{
			start = s;
			len = get_word_length(s);
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

char	**ft_split_whitespace(char const *s)
{
	char	**array;
	int		words;
	int		i;

	if (s == NULL)
		return (NULL);
	words = count_words(s);
	array = malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	return (push_words_in_array(array, s, i));
}
