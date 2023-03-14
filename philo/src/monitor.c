/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:52:18 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 19:43:26 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_bool	should_terminate(t_data *data)
{
	t_bool	should_terminate;

	pthread_mutex_lock(&data->terminate_mutex);
	should_terminate = data->terminate;
	pthread_mutex_unlock(&data->terminate_mutex);
	return (should_terminate);
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

void	toggle_terminate(t_data *data)
{
	pthread_mutex_lock(&data->terminate_mutex);
	data->terminate = true;
	pthread_mutex_unlock(&data->terminate_mutex);
}

void	monitor_philosophers(t_data *data)
{
	t_bool	full;
	int		i;
	t_philo	**philos;

	philos = data->philosophers;
	full = true;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (is_dead(philos[i]))
		{
			print_message(DIE, philos[i]);
			toggle_terminate(data);
		}
		if (!is_full(philos[i]))
			full = false;
		i++;
	}
	if (data->number_of_meals >= 1 && full)
		toggle_terminate(data);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->number_of_meals == 0)
		return (NULL);
	while (!should_terminate(data))
	{
		monitor_philosophers(data);
		usleep(1000);
	}
	return (NULL);
}
