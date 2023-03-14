/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:56:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:35:32 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philosopher_pause(unsigned long time_to_pause, t_data *data)
{
	time_to_pause += get_time();
	while (get_time() < time_to_pause)
	{
		if (should_terminate(data))
			break ;
		usleep(50);
	}
}

void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
	print_message(FORK, philo);
	print_message(EAT, philo);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time_elapsed(philo->data->start);
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	philosopher_pause(philo->data->time_to_eat, philo->data);
	if (!should_terminate(philo->data))
	{
		pthread_mutex_lock(&philo->data->times_ate_mutex);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->data->times_ate_mutex);
	}
}

void	philosopher_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	print_message(SLEEP, philo);
	philosopher_pause(philo->data->time_to_sleep, philo->data);
}

void	philosopher_think(t_philo *philo)
{
	unsigned long	time_left;
	unsigned long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->last_meal_mutex);
	time_since_last_meal = get_time_elapsed(philo->data->start)
		- philo->last_meal;
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	time_left = philo->data->time_to_die
		- philo->data->time_to_eat - time_since_last_meal;
	time_left /= 4;
	if (time_left < 0
		|| time_left > philo->data->time_to_eat + philo->data->time_to_sleep)
		time_left = 0;
	print_message(THINK, philo);
	philosopher_pause(time_left, philo->data);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_meals == 0 || philo->data->time_to_die == 0)
		return (NULL);
	else if (philo->data->number_of_philosophers == 1)
		return (one_philosopher(philo));
	if (philo->index % 2 == 0)
		usleep(philo->data->time_to_die / 2);
	while (!should_terminate(philo->data))
	{
		if (is_full(philo))
			break ;
		philosopher_eat(philo);
		philosopher_sleep(philo);
		philosopher_think(philo);
	}
	return (NULL);
}
