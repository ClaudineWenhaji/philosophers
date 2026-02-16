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

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_to_eat;

	if (ac < MIN_ARG_NBR || ac > MAX_ARG_NBR)
		error("Invalid number of arguments\n");
	if (parsing(av) == 1)
		return (1);
	nbr = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		nbr_times_to_eat = ft_atoi(av[5]);
	else
		nbr_times_to_eat = -1;
	philo = malloc(sizeof(t_philo) * nbr);
	if (!philo)
		return (error("Memory allocation error\n"));
	forks = malloc(sizeof(pthread_mutex_t) * nbr);
	if (!forks)
		return (error("Memory allocation failed\n"));
	init_program(&program, philo);
	init_forks(forks, nbr);
	init_philos(philo, &program, forks, nbr, time_to_die, time_to_eat, time_to_sleep, nbr_times_to_eat);
	create_threads(&program, forks, nbr);
	destroy_all(NULL, &program, forks, nbr);
	return (0);
}
