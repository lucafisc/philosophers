/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:56:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/10 11:06:31 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


void *routine(void *arg)
{
	t_philo philo = *(t_philo *)arg;

	// printf("Philosopher n.%d has forks %d and %d\n", philo.index, philo.index, (philo.index + 1)%philo.number_of_philosophers);
	// printf("%llums\n", get_time_elapsed(philo.data->start));
	while (1)
	{
		
	
		// here philosophers will be allowed to lock their forks
		pthread_mutex_lock(&philo.data->mutex);
		
		pthread_mutex_lock(&philo.data->forks[philo.left_fork]);
		printf("%llums %d has taken the left fork\n",get_time_elapsed(philo.data->start) ,philo.index);
		pthread_mutex_lock(&philo.data->forks[philo.right_fork]);
		printf("%llums %d has taken the right fork\n",get_time_elapsed(philo.data->start), philo.index);
		
		// let other philosophers pick their forks
		pthread_mutex_unlock(&philo.data->mutex);
		
		// here philosophers will eat
	
		printf("%llums %d is eating\n",get_time_elapsed(philo.data->start), philo.index);
		usleep(philo.data->time_to_eat);
		philo.last_meal = get_time_elapsed(philo.data->start);
		// unlock both forks
		pthread_mutex_unlock(&philo.data->forks[philo.left_fork]);
		pthread_mutex_unlock(&philo.data->forks[philo.right_fork]);
		
		// sleep ?
		printf("%llums %d is sleeping\n",get_time_elapsed(philo.data->start), philo.index);
		usleep(philo.data->time_to_sleep);
		// think ?
		printf("%llums %d is thinking\n",get_time_elapsed(philo.data->start), philo.index);
	
	}
	printf("%llums %d died\n",get_time_elapsed(philo.data->start), philo.index);
	return (NULL);
}