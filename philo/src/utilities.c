/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:40:22 by bmetehri          #+#    #+#             */
/*   Updated: 2023/11/30 15:30:32 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(char *str)
{
	long	nb;
	int		neg;

	neg = 1;
	nb = 0;
	while (*str == '+' || *str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-')
	{
		neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb == 2147483648 && neg < 0)
		return (-2147483648);
	return ((int)nb * neg);
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_for_a_sec(long long time, t_philo_state *philo_state)
{
	long long	i;

	i = timestamp();
	while (!(philo_state->died))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

/*
	------ ft_atoi ------
	Permet to parse the value got by argv

	------ timestamp ------
	Permet to get the time right now in milliseconds

	------ sleep for a sec ------
	Permet to sleep (time) by sleep 50micro_sec portions of time

	------ time_diff ------
	calculate the diff between two times
*/