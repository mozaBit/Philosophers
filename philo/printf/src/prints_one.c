/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:23 by bmetehri          #+#    #+#             */
/*   Updated: 2023/01/16 14:24:23 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

size_t	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_putstr(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	if (!str)
		return (ft_putstr("(null)"));
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
	return (size);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_putnbr(int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		len += ft_putnbr(nbr / 10);
	}
	len += ft_putchar(nbr % 10 + 48);
	return (len);
}

size_t	ft_putunbr(unsigned int nbr)
{
	size_t	len;

	len = 0;
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	len += ft_putchar(nbr % 10 + 48);
	return (len);
}
