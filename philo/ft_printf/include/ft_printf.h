/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:25:40 by bmetehri          #+#    #+#             */
/*   Updated: 2023/01/28 08:05:45 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_exec_flag(char *str, va_list args);
int		ft_printf(const char *str_format, ...);
size_t	ft_putnbr(int nbr);
size_t	ft_putunbr(unsigned int nbr);
size_t	ft_putnbrl(long long nbr);
size_t	ft_strlen(char *str);
size_t	ft_putstr(char *str);
size_t	ft_putchar(char c);
size_t	ft_print_in_hexa_min(unsigned long addr);
size_t	ft_print_in_hexa_max(unsigned long addr);
void	print_stuff(char *tabaddr, int i, size_t *j);
size_t	ft_print_void_p(void *pointer);

#endif
