/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:00:33 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 15:09:26 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parsing(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| check_arg_content(av[1]) == 1)
		error("Invalid number of philosophers\n");
	if (ft_atoi(av[2]) <= 0 || check_arg_content(av[2]) == 1)
		error("Invalid time to die\n");
	if (ft_atoi(av[3]) <= 0 || check_arg_content(av[3]) == 1)
		error("Invalid time to eat\n");
	if (ft_atoi(av[4]) <= 0 || check_arg_content(av[4]) == 1)
		error("Invalid time to sleep\n");
	if (av[5] && (ft_atoi(av[5]) < 0 || check_arg_content(av[5]) == 1))
		error("Invalid nbr of times each philosopher must eat");
	return (0);
}
