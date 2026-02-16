/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:55:01 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 18:14:01 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_philo *philo, t_program *program, pthread_mutex_t *forks, int nbr, long time_to_die, long time_to_eat, long time_to_sleep, long nbr_times_to_eat)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = get_current_time();
	while (i < nbr)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meal_eaten = 0;
		philo[i].nbr_of_philos = nbr;
		philo[i].time_to_die = time_to_die;
		philo[i].time_to_eat = time_to_eat;
		philo[i].time_to_sleep = time_to_sleep;
		philo[i].nbr_times_to_eat = nbr_times_to_eat;
		philo[i].last_meal = start_time;
		philo[i].start_time = start_time;
		philo[i].dead = &program->dead_flag;
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + nbr - 1) % nbr];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philos = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
