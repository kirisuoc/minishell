/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:17 by erikcousill       #+#    #+#             */

#include "libftprintf.h"

static void	parse_format_flags_width(char **format, t_format *info)
{
	if (**format == '+')
	{
		info->flag_plus = 1;
		(*format)++;
		if (**format == ' ')
			(*format)++;
	}
	else if (**format == ' ')
	{
		info->flag_space = 1;
		(*format)++;
	}
	else if (**format == '#')
	{
		info->flag_hash = 1;
		(*format)++;
	}
}

static void	parse_format_identif(char **format, t_format *info)
{
	if (**format == 'd' || **format == 'i' || **format == 'c'
		|| **format == 's' || **format == 'p' || **format == 'u'
		|| **format == 'x' || **format == 'X' || **format == '%')
		info->specifier = **format;
}

void	parse_format(char **format, t_format *info)
{
	parse_format_flags_width(format, info);
	parse_format_identif(format, info);
}
