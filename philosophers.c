/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:47:52 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 15:14:22 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int ac, char **av, t_config *config)
{
	if (ac < MIN_ARG_NBR || ac > MAX_ARG_NBR)
		error("Invalid number of arguments\n");
	if (parsing(av) == 1)
		return (1);
	config->nbr = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		config->nbr_times_to_eat = ft_atoi(av[5]);
	else
		config->nbr_times_to_eat = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philo;
	t_config		config;
	pthread_mutex_t	*forks;

	if (parse_args(ac, av, &config))
		return (1);
	philo = malloc(sizeof(t_philo) * config.nbr);
	if (!philo)
		return (error("Memory allocation error\n"));
	forks = malloc(sizeof(pthread_mutex_t) * config.nbr);
	if (!forks)
		return (error("Memory allocation failed\n"));
	init_program(&program, philo);
	init_forks(forks, &config);
	init_philos(philo, &program, forks, &config);
	create_threads(&program, forks, config.nbr);
	destroy_all(NULL, &program, forks, config.nbr);
	return (0);
}
