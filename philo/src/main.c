/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:12:36 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:03:17 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!is_valid_input(argc, argv))
		return (print_error());
	data = init_data(argc, argv);
	if (data == NULL || init_threads(data) != 0 || join_threads(data) != 0)
		return (print_error());
	destroy_philo(data);
	return (0);
}
