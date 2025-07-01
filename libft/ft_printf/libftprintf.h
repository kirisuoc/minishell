/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:36:51 by ecousill          #+#    #+#             */
/*   Updated: 2025/07/01 20:57:25 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include "../libft.h"

typedef struct s_format
{
	int		flag_plus;
	int		flag_hash;
	int		flag_space;
	char	specifier;
}			t_format;

int		ft_printf(char const *format, ...);
void	parse_format(char **format, t_format *info);

// put_functions
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(long n);
int		ft_putnbr_hex(unsigned int nbr, const char *base);
int		ft_putnbr_ptr(unsigned long nbr, const char *base);
int		get_number_length(int number);

// aux_functions
int		manage_flags_d(t_format *info, int number);

// manage_specifiers
int		manage_d(t_format *info, va_list *args);
int		manage_p(unsigned long ptr);
int		manage_x(t_format *info, va_list *args);

#endif
