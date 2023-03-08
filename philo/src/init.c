/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:30:04 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/08 20:23:34 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	init_philo(int argc, char *argv[])
{
	t_data	data;
	int		i;

	data.number_of_philosophers = ft_atoi(argv[1]);
	data.number_of_times_eat = -1;
	if (argc == 6)
		data.number_of_times_eat = ft_atoi(argv[5]);
	i = 0;
	data.philosophers = malloc(sizeof(t_philo*) * data.number_of_philosophers);
	while (i < data.number_of_philosophers)
	{;
		data.philosophers[i] = malloc(sizeof(t_philo));
		data.philosophers[i]->index = i;
		data.philosophers[i]->number_of_philosophers = data.number_of_philosophers;
		data.philosophers[i]->time_to_die = ft_atoi(argv[2]);
		data.philosophers[i]->time_to_eat = ft_atoi(argv[3]);
		data.philosophers[i]->time_to_sleep = ft_atoi(argv[4]);
		i++;
	}
	printf("%d\n",data.philosophers[0]->time_to_die);
	return (data);
}

int	init_threads(t_data *data)
{
	int	i;


	data->threads = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->threads)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, data->philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}	
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->threads[i], NULL) != 0) {
            return (1);
        }
        printf("Thread %d has finished execution\n", i);
		i++;
	}
	return (0);
}