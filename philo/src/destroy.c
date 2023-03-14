/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:01:43 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:02:47 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		free(data->philosophers[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->last_meal_mutex);
	pthread_mutex_destroy(&data->times_ate_mutex);
	pthread_mutex_destroy(&data->terminate_mutex);
	free(data->forks);
	free(data->philosophers);
	free(data->threads);
	free(data);
}
