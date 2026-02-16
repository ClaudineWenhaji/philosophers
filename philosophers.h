/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:31:03 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/16 18:02:09 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# include "types.h"

# define    MIN_ARG_NBR 5
# define    MAX_ARG_NBR 6

int		parsing(char **av);
int		error(char *msg);
void	init_program(t_program *program, t_philo *philo);
void	init_forks(pthread_mutex_t *forks, int nbr);
void	init_philos(t_philo *philo, t_program *program,
			pthread_mutex_t *forks, int nbr, long time_to_die,
			long time_to_eat, long time_to_sleep, long nbr_times_to_eat);
int		create_threads(t_program *program, pthread_mutex_t *forks, int nbr);
void	*philo_routine(void *pointer);
int		dead_loop(t_philo *philo);
void	*thread_monitoring(void *pointer);
int		check_if_all_ate(t_philo *philos, int nbr);
int		check_if_dead(t_philo *philos, int nbr);
int		philosopher_dead(t_philo *philo, long time_to_die);
void	print_message(char *str, t_philo *philo, int id);
long	get_current_time(void);
int		ft_usleep(int milliseconds);
void	destroy_all(char *str, t_program *program,
			pthread_mutex_t *forks, int nbr);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

#endif
