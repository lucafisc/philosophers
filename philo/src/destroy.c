/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:01:43 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/08 19:55:41 by lde-ross         ###   ########.fr       */
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
		i++;
	}
	free(data->philosophers);
	free(data->threads);
}