/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:06:12 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 16:38:10 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	processing(t_philo_state *philo_state)
{
	int				idx;
	t_philosopher	*philos;

	idx = 0;
	philos = philo_state->philosophers;
	philo_state->f_timestamp = timestamp();
	printf("philos: %i\n", philo_state->nb_philos);
	while (idx < philo_state->nb_philos)
	{
		if (pthread_create(&(philos[idx].thread_id), NULL, \
p_thread, &(philos[idx])))
			error_print("Error\nUnable to create Thread");
		philos[idx].t_last_ate = timestamp();
		idx++;
	}
	death_checker(philo_state, philo_state->philosophers);
	exit_launcher(philo_state, philos);
}

void	*p_thread(void	*philo_void)
{
	int				idx;
	t_philosopher	*philo;
	t_philo_state	*state;

	idx = 0;
	philo = (t_philosopher *)philo_void;
	state = philo->philo_state;
	if (philo->id % 2)
		usleep(10000);
	while (!(state->died))
	{
		philo_eats(philo);
		if (state->all_ate)
			break ;
		action_print(state, philo->id, "is sleeping");
		sleep_for_a_sec(state->time_to_sleep, state);
		action_print(state, philo->id, "is thinking");
		idx++;
	}
	return (NULL);
}

void	philo_eats(t_philosopher *philo)
{
	t_philo_state	*state;

	state = philo->philo_state;
	pthread_mutex_lock(&(state->forks[philo->left_fork_id]));
	action_print(state, philo->id, "has taken a fork");
	pthread_mutex_lock(&(state->forks[philo->right_fork_id]));
	action_print(state, philo->id, "has taken a fork");
	pthread_mutex_lock(&(state->meal_check));
	action_print(state, philo->id, "is eating");
	philo->t_last_ate = timestamp();
	pthread_mutex_unlock(&(state->meal_check));
	sleep_for_a_sec(state->time_to_eat, state);
	philo->nb_ate += 1;
	pthread_mutex_unlock(&(state->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(state->forks[philo->right_fork_id]));
}

void	action_print(t_philo_state *philo_state, int id, char *str)
{
	pthread_mutex_lock(&(philo_state->display));
	if (!(philo_state->died))
	{
		printf("%lli ", timestamp() - philo_state->f_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo_state->display));
}
