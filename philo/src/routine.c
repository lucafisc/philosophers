/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:56:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/08 20:35:12 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int mails = 0;
pthread_mutex_t mutex;

void *routine(void* arg)
{
	sleep(1);
	t_philo philo = *(t_philo*)arg;
	printf("Philosopher n.%d has forks %d and %d\n", philo.index, philo.index, (philo.index + 1)%philo.number_of_philosophers);
	printf("%lu\n", get_time());
	return (NULL);
}