/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:41:46 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 18:59:43 by bmetehri         ###   ########.fr       */
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

/*
	------ check args ------
	check if we have at least 4 args and at most 5 args

	------ initialzer ------
		*	initilizes my philo_state structure based on the given input
		*	initilaizes my philosphoers based on the input given in argv
		*	initialize the mutex used to control access for :
				- forks (right & left)
				- eating the meal.
				- displaying action on the screen

	------ processing ------
		*	creating the appropriate for each philosopher
		*	the philo thread runs acting function which hnadle
			different philo action (eating, sleeping, eating)
		*	checking the death
		*	runs exit functions
*/