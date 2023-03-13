/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:12:36 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/13 15:28:37 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (is_valid_input(argc, argv))
	{
		data = init_data(argc, argv);
		init_threads(data);
		join_threads(data);
		destroy_philo(data);
		free(data);
	}
	else
		printf("error");
	return (0);
}