/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:25:55 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/19 11:22:24 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	long	start;

	print_message("is dreaming", philo, philo->id);
	start = get_current_time();
	while (get_current_time() - start < philo->time_to_sleep)
	{
		if (is_dead(philo))
			break ;
		usleep(50);
	}
}

void	one_philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

static void	handle_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(1);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(1);
		pthread_mutex_lock(philo->right_fork);
	}
	print_message("has taken a fork", philo, philo->id);
}

void	eat(t_philo *philo)
{
	long	start;

	if (philo->nbr_of_philos == 1)
	{
		one_philosopher_eat(philo);
		return ;
	}
	handle_forks(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	start = get_current_time();
	while (get_current_time() - start < philo->time_to_eat)
	{
		if (is_dead(philo))
			break ;
		usleep(50);
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
