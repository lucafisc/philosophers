/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:56:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/09 20:15:07 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


void *routine(void *arg)
{
	t_philo philo = *(t_philo *)arg;

	// printf("Philosopher n.%d has forks %d and %d\n", philo.index, philo.index, (philo.index + 1)%philo.number_of_philosophers);
	// printf("%lu\n", get_time());

		printf("Philosopher %d is waiting for the mutex\n", philo.index);
		// here philosophers will be allowed to lock their forks
		pthread_mutex_lock(&philo.data->mutex);
		
		pthread_mutex_lock(&philo.data->forks[philo.left_fork]);
		printf("%lu %d has taken the left fork\n",get_time() ,philo.index);
		pthread_mutex_lock(&philo.data->forks[philo.right_fork]);
		printf("%lu %d has taken the right fork\n",get_time(), philo.index);
		
		// let other philosophers pick their forks
		pthread_mutex_unlock(&philo.data->mutex);
		
		// here philosophers will eat
	
		printf("%lu %d is eating\n",get_time(), philo.index);
		usleep(philo.data->time_to_eat);
		philo.last_meal = get_time();
		// unlock both forks
		pthread_mutex_unlock(&philo.data->forks[philo.left_fork]);
		pthread_mutex_unlock(&philo.data->forks[philo.right_fork]);
		
		// sleep ?
		printf("%lu %d is sleeping\n",get_time(), philo.index);
		usleep(philo.data->time_to_sleep);
		// think ?
		printf("%lu %d is thinking\n",get_time(), philo.index);
	
	printf("\n\n%lu %d died\n\n\n",get_time(), philo.index);
	return (NULL);
}