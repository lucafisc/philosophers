/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:56:57 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 14:19:39 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philosopher_pause(unsigned long time_to_pause, t_data *data)
{
	time_to_pause += get_time();
	while (get_time() < time_to_pause)
	{
		if (should_terminate(data))
			break;
		usleep(50);
	}
}

void	philosopher_eat(t_philo *philo)
{
	if (!should_terminate(philo->data))
	{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
	print_message(FORK, philo);
	print_message(EAT, philo);
	}
	philo->last_meal = get_time_elapsed(philo->data->start); //locked ?
	philosopher_pause(philo->data->time_to_eat, philo->data);
	if (!should_terminate(philo->data))
		philo->times_ate += 1; //if sim is running? (locked)
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
	
	time_since_last_meal = get_time_elapsed(philo->data->start) - philo->last_meal;
	//printf("philo[%d] time since last meal: %lu\n", philo->index, philo->last_meal);
	//printf("get_time_elapsed: %lums - last_meal: %lums\n", get_time_elapsed(philo->data->start), philo->last_meal);
	time_left = philo->data->time_to_die - philo->data->time_to_eat - time_since_last_meal;
	//printf("**%d time left = time_to_die: %lums - time to eat: %lums - last meal: %lums**\n",philo->index, philo->data->time_to_die, philo->data->time_to_eat, time_since_last_meal);
	//printf("time_left = time_to_die: %lums - time_to_eat: %lums - time_since_last_meal: %lums\n", philo->data->time_to_die ,philo->data->time_to_eat , time_since_last_meal);
	
	time_left /= 2; // basically how much time he has left divided by two
	if (time_left < 0)
		time_left = 0;
	// if (time_left > 200)
	// 	time_left = 50;
	// if more than x set it to a limit
	// think ?
	time_left = 0;
	printf("thiking for %lu \n", time_left);
	print_message(THINK, philo);
	//printf("**thinking for %lu**\n", time_left);
	philosopher_pause(time_left, philo->data);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->data->number_of_meals == 0 || philo->data->time_to_die == 0)
		return (NULL);
	//philo->last_meal = philo->data->start; //locked
	// delay?
	// if only one philo -> return separate function call
	// if philo is par -> go think
	
	// loop
	if (philo->index % 2 == 0)
		usleep(philo->data->time_to_die / 2);
	while (!should_terminate(philo->data))
	{
		if (philo->data->number_of_meals >= 1 && philo->times_ate >= philo->data->number_of_meals)
			break;
		philosopher_eat(philo);
		philosopher_sleep(philo);
		philosopher_think(philo);
	}

	//printf("%lums %d died\n",get_time_elapsed(philo.data->start), philo.index);
	return (NULL);
}