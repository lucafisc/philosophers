/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:52:18 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:39:10 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
