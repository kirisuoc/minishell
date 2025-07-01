/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:18:49 by ecousill          #+#    #+#             */
/*   Updated: 2025/07/01 20:52:00 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	manage_negative(int *n)
{
	if (*n < 0)
	{
		*n = -*n;
		return (1);
	}
	return (0);
}

static int	count_digits(int n)
{
	int		num_digits;
	int		temp;

	num_digits = 0;
	temp = n;
	if (n < 0)
	{
		temp = -temp;
	}
	while (temp > 0)
	{
		temp /= 10;
		num_digits++;
	}
	return (num_digits);
}

static char	*build_string(int n, char *s, int is_negative, int num_digits)
{
	int		divisor;
	int		digit;
	int		i;

	divisor = 1;
	while (num_digits-- > 1)
		divisor *= 10;
	i = 0;
	if (is_negative)
		s[i++] = '-';
	while (divisor > 0)
	{
		digit = n / divisor;
		s[i++] = digit + '0';
		n %= divisor;
		divisor /= 10;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		num_digits;
	int		is_negative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
	{
		string = malloc(2);
		if (!string)
			return (NULL);
		string[0] = '0';
		string[1] = '\0';
		return (string);
	}
	num_digits = count_digits(n);
	is_negative = manage_negative(&n);
	string = malloc(num_digits + is_negative + 1);
	if (!string)
		return (NULL);
	string = build_string(n, string, is_negative, num_digits);
	return (string);
}
