/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:42:14 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/29 19:00:05 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../ft_printf/include/ft_printf.h"

/*
	t_philosopher
*/
typedef struct s_philosopher
{
	int						id;
	int						nb_ate;
	int						left_fork_id;
	int						right_fork_id;
	long					t_last_ate;
	struct s_philo_state	*philo_state;
	pthread_t				thread_id;
}	t_philosopher;

typedef struct s_philo_state
{
	int						nb_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_must_eat;
	int						died;
	int						all_ate;
	long long				f_timestamp;
	pthread_mutex_t			meal_check;
	pthread_mutex_t			forks[250];
	pthread_mutex_t			display;
	struct s_philosopher	philosophers[250];
}	t_philo_state;

/*
	Checking
*/
void			check_args(int ac);

/*
	Erroring
*/
void			error_print(char *str);

/*
	intialising
*/
void			inializer(t_philo_state *philo_state, char **av);
void			mutex_initilizer(t_philo_state *philo_state);
void			philos_initilizer(t_philo_state	*philo_state);

/*
	utilities
*/
int				ft_atoi(char *str);
long long		timestamp(void);

/*
	processing
*/
void			processing(t_philo_state *philo_state);
void			*acting(void	*philo_void);
void			action_print(t_philo_state *philo_state, int id, char *str);
void			eating(t_philosopher *philo);
void			sleep_for_a_sec(long long time, t_philo_state *philo_state);
long long		time_diff(long long past, long long pres);
void			death_checker(t_philo_state *state, t_philosopher *p);
void			exit_launcher(t_philo_state *state, t_philosopher *philos);

#endif
