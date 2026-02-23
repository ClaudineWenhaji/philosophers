/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:25:55 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/23 19:16:46 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	start_eating(t_philo *philo)
{
	if (philo->nbr_of_philos == 1)
	{
		one_philosopher(philo);
		return ;
	}
	handle_forks(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
}

void	finish_eating(t_philo *philo)
{
	long	start;
	int		finished;

	finished = 1;
	start = get_current_time();
	while (get_current_time() - start < philo->time_to_eat - 1)
	{
		if (is_dead(philo))
		{
			finished = 0;
			break ;
		}
		usleep(200);
	}
	if (finished)
	{
		pthread_mutex_lock(philo->meal_lock);
		philo->meal_eaten++;
		pthread_mutex_unlock(philo->meal_lock);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	if (philo->nbr_of_philos == 1)
	{
		one_philosopher(philo);
		return ;
	}
	start_eating(philo);
	finish_eating(philo);
}
