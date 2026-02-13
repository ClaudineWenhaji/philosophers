/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:47:52 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/13 16:43:29 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
    t_program       *program;
    t_philo         *philo;
    pthread_mutex_t *forks;
    
    if (ac < MIN_ARG_NBR || ac > MAX_ARG_NBR)
        error("Invalid number of arguments\n");
    if (parsing(av) == 1);
        return (1);
    init_program(&program, philo);
    init_forks(forks, ft_atoi(av[1]));
    init_philos(philo, &program, forks, av);
    create_threads(&program, forks);
    destroy_all(NULL, &program, forks);
    return (0);
}