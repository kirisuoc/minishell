/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erikcousillas <erikcousillas@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:11 by ecousill          #+#    #+#             */

#include "libftprintf.h"

int	manage_d(t_format *info, va_list *args)
{
	int	printed_chars;
	int	number;

	printed_chars = 0;
	number = va_arg(*args, int);
	printed_chars += manage_flags_d(info, number);
	return (printed_chars);
}

int	manage_p(unsigned long ptr)
{
	int					printed_chars;
	const char			*base;

	printed_chars = 0;
	base = "0123456789abcdef";
	if (ptr == 0)
		printed_chars += ft_putstr("(nil)");
	else
	{
		printed_chars += ft_putstr("0x");
		printed_chars += ft_putnbr_ptr(ptr, base);
	}
	return (printed_chars);
}

int	manage_x(t_format *info, va_list *args)
{
	int				printed_chars;
	unsigned int	hexnumber;
	const char		*base;

	printed_chars = 0;
	hexnumber = va_arg(*args, unsigned int);
	if (info->specifier == 'x')
		base = "0123456789abcdef";
	else if (info->specifier == 'X')
		base = "0123456789ABCDEF";
	else
		return (0);
	if (info->flag_hash == 1 && hexnumber != 0)
	{
		if (info->specifier == 'x')
			printed_chars += ft_putstr("0x");
		else if (info->specifier == 'X')
			printed_chars += ft_putstr("0X");
	}
	printed_chars += ft_putnbr_hex(hexnumber, base);
	return (printed_chars);
}
