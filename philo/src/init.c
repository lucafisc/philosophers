/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:30:04 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:42:56 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_threads(t_data *data)
{
	int	i;

	data->threads = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->threads)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL,
				&routine, data->philosophers[i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor, data) != 0)
	{
		printf("Failed to create thread\n");
		return (2);
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
		{
			return (1);
		}
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (1);
	return (0);
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->index = i;
		philos[i]->first_fork = i;
		philos[i]->second_fork = (i + 1) % data->number_of_philosophers;
		if (i % 2 != 0)
		{
			philos[i]->first_fork = philos[i]->second_fork;
			philos[i]->second_fork = i;
		}
		philos[i]->times_ate = 0;
		philos[i]->last_meal = get_time_elapsed(data->start);
		philos[i]->data = data;
	}
	return (philos);
}

void	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_init(&data->times_ate_mutex, NULL);
	pthread_mutex_init(&data->terminate_mutex, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_meals = -1;
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	data->start = get_time();
	data->terminate = false;
	init_mutex(data);
	data->philosophers = init_philos(data);
	return (data);
}
