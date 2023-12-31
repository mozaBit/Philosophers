/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:06:12 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/30 15:49:56 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	processing(t_philo_state *philo_state)
{
	int				idx;
	t_philosopher	*ph;

	idx = -1;
	ph = philo_state->philosophers;
	philo_state->f_timestamp = timestamp();
	while (++idx < philo_state->nb_philos)
	{
		if (pthread_create(&(ph[idx].thread_id), NULL, acting, &(ph[idx])))
			error_print("Error\nUnable to create Thread");
		pthread_mutex_lock(&(philo_state->t_last_ate_mutex));
		ph[idx].t_last_ate = timestamp();
		pthread_mutex_unlock(&(philo_state->t_last_ate_mutex));
	}
	death_checker(philo_state, philo_state->philosophers);
	exit_launcher(philo_state, ph);
}

void	*acting(void	*philo_void)
{
	t_philosopher	*philo;
	t_philo_state	*state;

	philo = (t_philosopher *)philo_void;
	state = philo->philo_state;
	if (philo->id % 2)
		usleep(15000);
	pthread_mutex_lock(&(state->died_mutex));
	while (!(state->died))
	{

		pthread_mutex_unlock(&(state->died_mutex));
		eating(philo);
		if (philo->nb_ate >= 1)
		{
			action_print(state, philo->id, "is sleeping");
			sleep_for_a_sec(state->time_to_sleep, state);
			action_print(state, philo->id, "is thinking");
		}
		pthread_mutex_lock(&(state->all_ate_mutex));
		if (state->all_ate)
		{
			pthread_mutex_unlock(&(state->all_ate_mutex));
			break ;
		}
		pthread_mutex_unlock(&(state->all_ate_mutex));
		pthread_mutex_lock(&(state->died_mutex));
	}
	pthread_mutex_unlock(&(state->died_mutex));
	return (NULL);
}

void	eating(t_philosopher *philo)
{
	t_philo_state	*state;

	state = philo->philo_state;
	if (philo->philo_state->nb_philos >= 2)
	{
		take_forks(state, philo);
		pthread_mutex_lock(&(state->meal_check));
		action_print(state, philo->id, "is eating");
		pthread_mutex_lock(&(state->t_last_ate_mutex));
		philo->t_last_ate = timestamp();
		pthread_mutex_unlock(&(state->t_last_ate_mutex));
		sleep_for_a_sec(state->time_to_eat, state);
		philo->nb_ate += 1;
		pthread_mutex_unlock(&(state->meal_check));
		drop_forks(state, philo);
	}
}

void	action_print(t_philo_state *philo_state, int id, char *str)
{
	pthread_mutex_lock(&(philo_state->display));
	pthread_mutex_lock(&(philo_state->died_mutex));
	if (!(philo_state->died))
	{
		printf("%lli ", timestamp() - philo_state->f_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo_state->died_mutex));
	pthread_mutex_unlock(&(philo_state->display));
}

/*
	------ processing ------
	*	create and runs the the thread for each philosophers (acting)
	*	runs the death_checker func that checks if there is a dead philo
	*	runs after all the exit function (wich joins threads and destroy mutexs)

	------ acting ------
	*	runs for each philosopher
	*	takes a void * of a philosopher
	*	takes the state of the game from the philo struct
	*	runs eating and eating function for each philo
	*	runs the impair philo first
	*	then after eating runs the sleeping and the thinking processs for each philo

	------ eating ------
	*	holds (locks) the right and left fork of each philo
	*	proccess the eating procces and wait for the right time
	*	adds into philo->number_of_time_eaten
	*	unlock the forks

	------ action print ------ Done
	*	prints the action happening using ft_orintf and a mutex
		to not have aconflict while printing multiple nonsense
*/