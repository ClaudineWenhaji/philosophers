/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_join_thread.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:36:04 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/23 19:38:15 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dead_loop checks if the value of dead_flag changed
// philo_routine is the thread routine
// create_threads creates all the threads

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->dead_lock);
	dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (dead);
}

static void	philo_loop(t_philo *philo)
{
	while (1)
	{
		if (is_dead(philo))
			break ;
		pthread_mutex_lock(philo->meal_lock);
		if (philo->nbr_times_to_eat != -1
			&& philo->meal_eaten >= philo->nbr_times_to_eat)
		{
			pthread_mutex_unlock(philo->meal_lock);
			break ;
		}
		pthread_mutex_unlock(philo->meal_lock);
		eat(philo);
		dream(philo);
		think(philo);
	}
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(200);
	if (philo->nbr_of_philos % 2 != 0)
	{
		if (philo->id == philo->nbr_of_philos)
			ft_usleep(philo->time_to_eat * 2);
	}
	philo_loop(philo);
	return (NULL);
}

int	create_threads(t_program *program, pthread_mutex_t *forks, int nbr)
{
	pthread_t	observer;
	int			i;

	i = 0;
	while (i < nbr)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philo_routine,
				&program->philos[i]) != 0)
			destroy_all("Thread creation error", program, forks, nbr);
		i++;
	}
	if (pthread_create(&observer, NULL, thread_monitoring, program) != 0)
		destroy_all("Thread creation error", program, forks, nbr);
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", program, forks, nbr);
	i = 0;
	while (i < nbr)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", program, forks, nbr);
		i++;
	}
	return (0);
}
