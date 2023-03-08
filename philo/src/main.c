/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:12:36 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/08 19:53:15 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (is_valid_input(argc, argv))
	{
		data = init_philo(argc, argv);
		init_threads(&data);
		join_threads(&data);
		destroy_philo(&data);
	}
	else
		printf("error");

	return (0);
}