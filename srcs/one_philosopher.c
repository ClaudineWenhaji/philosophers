/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:31:46 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/23 19:09:34 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

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
		usleep(200);
	}
}
