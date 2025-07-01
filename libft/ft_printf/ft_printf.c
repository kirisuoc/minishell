/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:57:10 by ecousill          #+#    #+#             */

#include "libftprintf.h"

static int	process_format(t_format *info, va_list *args)
{
	int	printed_chars;

	printed_chars = 0;
	if (info->specifier == 'c')
		printed_chars += ft_putchar(va_arg(*args, int));
	else if (info->specifier == 'd' || info->specifier == 'i')
		printed_chars += manage_d(info, args);
	else if (info->specifier == 'p')
		printed_chars += manage_p(va_arg(*args, unsigned long));
	else if (info->specifier == 's')
		printed_chars += ft_putstr(va_arg(*args, char *));
	else if (info->specifier == 'u')
		printed_chars += ft_putnbr(va_arg(*args, unsigned int));
	else if (info->specifier == 'x' || info->specifier == 'X')
		printed_chars += manage_x(info, args);
	else if (info->specifier == '%')
		printed_chars += ft_putchar('%');
	return (printed_chars);
}

int	ft_printf(char const *format, ...)
{
	int			count;
	char		*format_copy;
	t_format	info;
	va_list		args;

	va_start(args, format);
	count = 0;
	format_copy = (char *)format;
	while (*format_copy)
	{
		if (*format_copy == '%' && *(format_copy + 1))
		{
			format_copy++;
			ft_bzero(&info, sizeof(info));
			parse_format(&format_copy, &info);
			count += process_format(&info, &args);
		}
		else
			count += ft_putchar(*format_copy);
		format_copy++;
	}
	va_end(args);
	return (count);
}
