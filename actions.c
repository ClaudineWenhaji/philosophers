/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:25:55 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/18 10:57:47 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message("is dreaming", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	one_philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!dead_loop(philo))
		print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->right_fork);
}

static int	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	if (dead_loop(philo))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_message("has taken a fork", philo, philo->id);
	return (1);
}

void	eat(t_philo *philo)
{
	if (philo->nbr_of_philos == 1)
	{
		one_philosopher_eat(philo);
		return ;
	}
	if ((philo->id % 2 == 0 && !take_fork(philo->left_fork, philo))
		|| !take_fork(philo->right_fork, philo)
		|| (philo->id % 2 != 0 && !take_fork(philo->left_fork, philo)))
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	if (!dead_loop(philo))
		print_message("is eating", philo, philo->id);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
