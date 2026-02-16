/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:19:48 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 13:04:56 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "philosophers.h"

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eating;
	int			meal_eaten;
	long		last_meal;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			nbr_of_philos;
	int			nbr_times_to_eat;
	int			*dead;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;

#endif
