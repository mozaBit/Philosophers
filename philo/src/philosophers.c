/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:41:46 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 11:56:41 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	t_philo_state	philo_state;

	check_args(ac);
	inializer(&philo_state, av);
	processing(&philo_state);
	return (EXIT_SUCCESS);
}
