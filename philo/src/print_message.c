/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:34:36 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:00:42 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/colors.h"

void	print_message(int message, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_time_elapsed(philo->data->start);
	if (!should_terminate(philo->data))
	{
		if (message == FORK)
			printf("%s%ums %s%d has taken a fork%s\n",
				BWHT, timestamp, BMAG, philo->index, RESET);
		else if (message == EAT)
			printf("%s%ums %s%d is eating%s\n",
				BWHT, timestamp, BGRN, philo->index, RESET);
		else if (message == SLEEP)
			printf("%s%ums %s%d is sleeping%s\n",
				BWHT, timestamp, BBLU, philo->index, RESET);
		else if (message == THINK)
			printf("%s%ums %s%d is thinking%s\n",
				BWHT, timestamp, BYEL, philo->index, RESET);
		else if (message == DIE)
			printf("%s%ums %s%d died%s\n",
				BWHT, timestamp, BRED, philo->index, RESET);
	}
}

int	print_error(void)
{
	write(STDERR_FILENO, "error", 5);
	return (1);
}
