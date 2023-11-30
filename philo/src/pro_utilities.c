/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:57:37 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/30 15:02:02 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo_state *state ,t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(state->forks[philo->left_fork_id]));
		action_print(state, philo->id, "has taken a left fork");
		pthread_mutex_lock(&(state->forks[philo->right_fork_id]));
		action_print(state, philo->id, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(&(state->forks[philo->right_fork_id]));
		action_print(state, philo->id, "has taken a right fork");
		pthread_mutex_lock(&(state->forks[philo->left_fork_id]));
		action_print(state, philo->id, "has taken a left fork");
	}
}


void	drop_forks(t_philo_state *state ,t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&(state->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(state->forks[philo->right_fork_id]));
	}
	else
	{
		pthread_mutex_unlock(&(state->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(state->forks[philo->left_fork_id]));
	}
}