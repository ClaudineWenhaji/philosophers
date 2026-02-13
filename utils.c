/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:09:53 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/13 16:24:11 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strlen(char *str)
{
    int i;
    
    if (str == NULL)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_atoi(char *str)
{
    int i;
    int sum;
    
    i = 0;
    sum = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+')
        i++;
    if (str[i] == '-')
        return (-1);
    while (str[i] >= '0' && str[i] <= '9')
    {
        sum = sum * 10 + (str[i] - '0');
        if (sum > INT_MAX)
            return (-1);
        i++;
    }
    if (str[i] != '\0')
        return (-1);
    return ((int)sum);
}

void    destroy_all(char *str, t_program *program, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    if (str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->dead_lock);
    while( i < program->philos[0].nbr_of_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    
}

int ft_usleep(int milliseconds)
{
    int start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}

int get_current_time(void)
{
    struct timeval  time;
    
    if (gettimeofday(&time, NULL) == -1)
        error("gettimeofday() error\n");
    return (time.tv_sec * 1000 + time.tv_sec / 1000);
}