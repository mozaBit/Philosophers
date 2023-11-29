/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:38:54 by bmetehri          #+#    #+#             */
/*   Updated: 2023/01/28 08:02:52 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_exec_flag(char *str, va_list args);

int	ft_printf(const char *str_format, ...)
{
	va_list	args;
	size_t	nbr_of_chr;

	nbr_of_chr = 0;
	if (!str_format)
		return (0);
	va_start(args, str_format);
	while (*str_format)
	{
		if (*str_format == '%')
		{
			nbr_of_chr += ft_exec_flag((char *)str_format, args);
			str_format++;
		}
		else
			nbr_of_chr += ft_putchar(*str_format);
		str_format++;
	}
	va_end(args);
	return ((int)nbr_of_chr);
}

int	ft_exec_flag(char *str, va_list args)
{
	if (*(str + 1) == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (*(str + 1) == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (*(str + 1) == 'p')
		return (ft_print_void_p(va_arg(args, void *)));
	if (*(str + 1) == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (*(str + 1) == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (*(str + 1) == 'l')
		return (ft_putnbrl(va_arg(args, long long)));
	if (*(str + 1) == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	if (*(str + 1) == 'x')
		return (ft_print_in_hexa_min(va_arg(args, unsigned int)));
	if (*(str + 1) == 'X')
		return (ft_print_in_hexa_max(va_arg(args, unsigned int)));
	if (*(str + 1) == '%')
		return (ft_putchar('%'));
	return (0);
}
