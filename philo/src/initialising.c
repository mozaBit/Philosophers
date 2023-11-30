/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:36:08 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/30 12:45:09 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	inializer(t_philo_state *philo_state, char **av)
{
	philo_state->nb_philos = ft_atoi(av[1]);
	philo_state->time_to_die = ft_atoi(av[2]);
	philo_state->time_to_eat = ft_atoi(av[3]);
	philo_state->time_to_sleep = ft_atoi(av[4]);
	philo_state->all_ate = 0;
	philo_state->died = 0;
	if (av[5])
	{
		philo_state->nb_must_eat = ft_atoi(av[5]);
		if (philo_state->nb_must_eat <= 0)
			error_print("Error\nWrong Number \
of times each Philosopher must eat");
	}
	else
	{
		philo_state->nb_must_eat = -1;
	}
	if (philo_state->nb_philos < 1 || philo_state->nb_philos > 250
		|| philo_state->time_to_die < 0 || philo_state->time_to_eat < 0
		|| philo_state->time_to_sleep < 0)
		error_print("Error\nWrong Value of one or more Args");
	mutex_initilizer(philo_state);
	philos_initilizer(philo_state);
}

void	mutex_initilizer(t_philo_state *philo_state)
{
	int	idx;

	idx = philo_state->nb_philos;
	while (--idx >= 0)
	{
		if (pthread_mutex_init(&(philo_state->forks[idx]), NULL))
			error_print("Error\nWhile Initiqlizing a mutex");
	}
	if (pthread_mutex_init(&(philo_state->display), NULL)
		|| pthread_mutex_init(&(philo_state->meal_check), NULL)
		|| pthread_mutex_init(&(philo_state->all_ate_mutex), NULL)
		|| pthread_mutex_init(&(philo_state->died_mutex), NULL)
		|| pthread_mutex_init(&(philo_state->t_last_ate_mutex), NULL))
		error_print("Error\nWhile Initiqlizing a mutex");
}

void	philos_initilizer(t_philo_state	*state)
{
	int	idx;

	idx = state->nb_philos;
	while (--idx >= 0)
	{
		state->philosophers[idx].id = idx;
		state->philosophers[idx].nb_ate = 0;
		state->philosophers[idx].left_fork_id = idx;
		state->philosophers[idx].right_fork_id = (idx + 1) % state->nb_philos;
		state->philosophers[idx].t_last_ate = 0;
		state->philosophers[idx].philo_state = state;
	}
}

/*
	------ Initializer ------
	fills the philo_state structure with the appropriate values from the argv
	runs the mutex_initilizer and the philo_initilizer

	------ mutex initializer ------
	*	Initilizes all the forks (number of forks == number of philos)
	*	Initilize the printing mutex (display) to prevent from printin multiple
		nonesence the same time
	*	Initilize the eating mutex (meal_check) to prevent from two philos
		eating the same time

	------ philo_initializer ------
	*	initialize the philo structure with all neccessary values
*/