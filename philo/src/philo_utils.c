/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:27:51 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:50:41 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_bool	is_full(t_philo *philo)
{
	t_bool	full;
	int		times_ate;

	full = false;
	pthread_mutex_lock(&philo->data->times_ate_mutex);
	times_ate = philo->times_ate;
	pthread_mutex_unlock(&philo->data->times_ate_mutex);
	if (philo->data->number_of_meals >= 1
		&& times_ate >= philo->data->number_of_meals)
		full = true;
	return (full);
}

t_bool	is_dead(t_philo *philo)
{
	u_int64_t	current_time;
	t_bool		is_dead;

	is_dead = false;
	current_time = get_time_elapsed(philo->data->start);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	if (current_time - philo->last_meal > philo->data->time_to_die)
		is_dead = true;
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	return (is_dead);
}

t_bool	should_terminate(t_data *data)
{
	t_bool	should_terminate;

	pthread_mutex_lock(&data->terminate_mutex);
	should_terminate = data->terminate;
	pthread_mutex_unlock(&data->terminate_mutex);
	return (should_terminate);
}

void	toggle_terminate(t_data *data)
{
	pthread_mutex_lock(&data->terminate_mutex);
	data->terminate = true;
	pthread_mutex_unlock(&data->terminate_mutex);
}

void	*one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	print_message(FORK, philo);
	while (!should_terminate(philo->data))
		usleep(1000);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
	return (NULL);
}
