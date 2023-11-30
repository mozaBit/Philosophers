/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:45:35 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/30 15:55:01 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	check_args(int ac)
{
	if (ac != 5 && ac != 6)
		error_print("Error\nInavlid Input Arguments");
}

void	exit_launcher(t_philo_state *state, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < state->nb_philos)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < state->nb_philos)
		pthread_mutex_destroy(&(state->forks[i]));
	pthread_mutex_destroy(&(state->display));
	pthread_mutex_destroy(&(state->t_last_ate_mutex));
	pthread_mutex_destroy(&(state->died_mutex));
	pthread_mutex_destroy(&(state->all_ate_mutex));
	pthread_mutex_destroy(&(state->meal_check));
}

void	death_checker(t_philo_state *state, t_philosopher *p)
{
	int	i;

	pthread_mutex_lock(&(state->all_ate_mutex));
	while (!(state->all_ate))
	{
		pthread_mutex_unlock(&(state->all_ate_mutex));
		i = -1;
		pthread_mutex_lock(&(state->meal_check));
		pthread_mutex_lock(&(state->t_last_ate_mutex));
		while (++i < state->nb_philos && !(state->died))
		{
			if (time_diff(p[i].t_last_ate, timestamp()) > state->time_to_die)
			{
				pthread_mutex_lock(&(state->died_mutex));
				action_print(state, i, "died");
				state->died = 1;
				pthread_mutex_unlock(&(state->died_mutex));
			}
			usleep(100);
		}
		pthread_mutex_unlock(&(state->meal_check));
		pthread_mutex_unlock(&(state->t_last_ate_mutex));
		pthread_mutex_lock(&(state->died_mutex));
		if (state->died)
		{
			pthread_mutex_unlock(&(state->died_mutex));
			break ;
		}
		pthread_mutex_unlock(&(state->died_mutex));
		i = 0;
		while (state->nb_must_eat != -1 && i < state->nb_philos
			&& p[i].nb_ate >= state->nb_must_eat)
			i++;
		if (i == state->nb_philos)
		{
			pthread_mutex_lock(&(state->all_ate_mutex));
			state->all_ate = 1;
			pthread_mutex_unlock(&(state->all_ate_mutex));
		}
		pthread_mutex_lock(&(state->all_ate_mutex));
	}
		pthread_mutex_unlock(&(state->all_ate_mutex));
}

/*
	------ check args ------
	check if we have at least 4 args and at most 5 args

	------ death checker ------
	checks for a dead philosopher
		*	if his last_meal is bigger (>) then time_to_die
	handle the all_ate state, when all philos ate at least (number
		of meals must eaten times)

	------ exit checker ------
	Joins the threads and destroys the mutexes
*/