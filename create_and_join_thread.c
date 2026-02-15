/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_join_thread.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:36:04 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/13 16:54:49 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dead_loop checks if the value of dead_flag changed
// philo_routine is the thread routine
// create_threads creates all the threads

#include "philosophers.h"

int dead_loop(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead == 1)
        return (pthread_mutex_unlock(philo->dead_lock), 1);
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}

void    *philo_routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *)pointer;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (!dead_loop(philo))
    {
        eat(philo);
        dream(philo);
        think(philo);
    }
    return (pointer);
}

int create_threads(t_program *program, pthread_mutex_t *forks, int nbr)
{
    pthread_t observer;
    int             i;
  
    i = 0;
    while (i < nbr)
    {
        if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
            &program->philos[i]) != 0)
            destroy_all("Thread creation error", program, forks, nbr);
        i++;
    }
    if (pthread_create(&observer, NULL, &thread_monitoring, program->philos) != 0)
        destroy_all("Thread creation error", program, forks, nbr);
    i = 0;
    if (pthread_join(observer, NULL) != 0)
        destroy_all("Thread join error", program, forks, nbr);
    while (i < nbr)
    {
        if (pthread_join(program->philos[i].thread, NULL) != 0)
            destroy_all("Thread join error", program, forks, nbr);
        i++;
    }
    return (0);
}