/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:27:51 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 19:32:05 by lde-ross         ###   ########.fr       */
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
