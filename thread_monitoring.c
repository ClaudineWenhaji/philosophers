/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:23:23 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 17:45:04 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo, int id)
{
	long	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo) || ft_strcmp(str, "died") == 0)
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	philosopher_dead(t_philo *philo, long time_to_die)
{
	long	current_time;

	pthread_mutex_lock(philo->meal_lock);
	current_time = get_current_time();
	if (current_time - philo->last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos[0].dead_lock);
			if (*(philos[0].dead) == 0)
			{
				*(philos[0].dead) = 1;
				pthread_mutex_unlock(philos[0].dead_lock);
				print_message("died", &philos[i], philos[i].id);
				return (1);
			}
			pthread_mutex_unlock(philos[0].dead_lock);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos, int nbr)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].nbr_times_to_eat == -1)
		return (0);
	while (i < nbr)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meal_eaten >= philos[i].nbr_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*thread_monitoring(void *pointer)
{
	t_program	*program;

	program = (t_program *)pointer;
	while (1)
	{
		if (check_if_dead(program->philos, program->philos[0].nbr_of_philos)
			|| check_if_all_ate(program->philos, program->philos[0].nbr_of_philos))
			break ;
		ft_usleep(500);
	}
	return (NULL);
}
