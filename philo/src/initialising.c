/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:36:08 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 12:07:12 by bmetehri         ###   ########.fr       */
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
	if (philo_state->nb_philos < 2 || philo_state->nb_philos > 250
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
		if (pthread_mutex_init(&(philo_state->forks[idx]), NULL)
			|| pthread_mutex_init(&(philo_state->display), NULL)
			|| pthread_mutex_init(&(philo_state->meal_check), NULL))
			error_print("Error\nWhile Initiqlizing a mutex");
	}
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
