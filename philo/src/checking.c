/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:45:35 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 13:37:24 by bmetehri         ###   ########.fr       */
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
}

void	death_checker(t_philo_state *state, t_philosopher *p)
{
	int	i;

	while (!(state->all_ate))
	{
		i = -1;
		while (++i < state->nb_philos && !(state->died))
		{
			pthread_mutex_lock(&(state->meal_check));
			if (time_diff(p[i].t_last_ate, timestamp()) > state->time_to_die)
			{
				action_print(state, i, "died");
				state->died = 1;
			}
			pthread_mutex_unlock(&(state->meal_check));
			usleep(100);
		}
		if (state->died)
			break ;
		i = 0;
		while (state->nb_must_eat != -1 && i < state->nb_philos
			&& p[i].nb_ate >= state->nb_must_eat)
			i++;
		if (i == state->nb_philos)
			state->all_ate = 1;
	}
}
