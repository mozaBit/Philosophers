/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:16:40 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 11:30:48 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	error_print(char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	write(1, str, length);
	write(1, "\n", 1);
	return (exit(1));
}
