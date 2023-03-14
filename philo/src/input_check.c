/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:52:26 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:20:04 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (ft_is_sign(str[i]))
	{
		if (str[i] == '-')
			return (false);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

t_bool	is_valid_input(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (false);
		i++;
	}
	if (ft_atoi(argv[1]) <= 0)
		return (false);
	return (true);
}
