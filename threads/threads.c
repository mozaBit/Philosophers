// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   threads.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/11/20 17:45:11 by bmetehri          #+#    #+#             */
// /*   Updated: 2023/11/20 19:53:30 by bmetehri         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

/*
	A short introduction about threads in C
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	*adding_same_mil_times(void *value);

int	main(int ac , char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			value1;
	int			value2;

	value1 = 7;
	value2 = 4;

	// adding_same_mil_times( (void *) &value1);
	// adding_same_mil_times( (void *) &value2);

	pthread_create(&thread1, NULL, adding_same_mil_times, (void *) &value1);
	pthread_create(&thread2, NULL, adding_same_mil_times, (void *) &value2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (EXIT_SUCCESS);
}

void	*adding_same_mil_times(void *value)
{
	size_t		sum;
	long		idx;
	size_t	*mine;

	idx = 0;
	mine = (size_t *) value;
	while (idx++ < 10000000000)
		sum +=	*mine;
	return (NULL);
}