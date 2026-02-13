/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:23:23 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/02/13 16:07:37 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*int get_stop(t_data *data)
{
    int value;

    pthread_mutex_lock(&data->stop_mutex);
    value = data->stop;
    pthread_mutex_unlock(&data->stop_mutex);
    return (value);
}

void set_stop(t_data *data, int value)
{
    pthread_mutex_lock(&data->stop_mutex);
    data->stop = value;
    pthread_mutex_unlock(&data->stop_mutex);
}

void print_status(t_data *data, int id, char *msg)
{
    pthread_mutex_lock(&data->print_mutex);
    if (!get_stop(data))
        printf("%ld %d %s\n",
            get_time() - data->start_time,
            id,
            msg);
    pthread_mutex_unlock(&data->print_mutex);
}

void *monitor(void *arg)
{
    t_data  *data;
    int     i;
    long    now;

    data = (t_data *)arg;

    while (!get_stop(data))
    {
        i = 0;
        while (i < data->nbr_of_philo && !get_stop(data))
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            now = get_time();
            if (now - data->philos[i].last_meal >= data->time_to_die)
            {
                pthread_mutex_unlock(&data->philos[i].meal_mutex);

                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n",
                    now - data->start_time,
                    data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                set_stop(data, 1);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            i++;
        }

        // Vérification si tous ont mangé assez (si must_eat activé)
        if (data->must_eat > 0)
        {
            i = 0;
            int finished = 1;
            while (i < data->nb_philo)
            {
                pthread_mutex_lock(&data->philos[i].meal_mutex);
                if (data->philos[i].meals_eaten < data->must_eat)
                    finished = 0;
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
                i++;
            }
            if (finished)
            {
                set_stop(data, 1);
                return (NULL);
            }
        }

        usleep(1000); // évite de surcharger le CPU
    }
    return (NULL);
} */

void    print_message(char *str, t_philo *philo, int id)
{
    int time;
    
    pthread_mutex_lock(philo->write_lock);
    time = get_current_time() - philo->start_time;
    if (!dead_loop(philo))
        printf("%d %d %s\n", time, id, str);
    pthread_mutex_unlock(philo->write_lock);
}

int philosopher_dead(t_philo *philo, int time_to_die)
{
    pthread_mutex_lock(philo->meal_lock);
    if (get_current_time() - philo->last_meal >= time_to_die
        && philo->eating == 0)
        return (pthread_mutex_unlock(philo->meal_lock), 1);
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

int check_if_dead(t_philo *philos)
{
    int i;
    
    i = 0;
    while (i < philos[0].nbr_of_philos)
    {
        if (philosopher_dead(&philos[i], philos[i].time_to_die))
        {
            print_message("died", &philos[i], philos[i].id);
            pthread_mutex_lock(philos[0].dead_lock);
            *philos->dead = 1;
            pthread_mutex_unlock(philos[0].dead_lock);
            return (1);
        }
        i++;
    }
    return (0);
}

int check_if_all_ate(t_philo *philos)
{
    int i;
    int finishd_eating;

    if (philos[0].nbr_times_to_eat == -1)
        return (0);
    while(i < philos[0].nbr_of_philos)
    {
        pthread_mutex_lock(philos[i].meal_lock);
        if (philos[i].meal_eaten >= philos[i].nbr_times_to_eat)
            finishd_eating++;
        pthread_mutex_unlock(philos[i].meal_lock);
    }
    if (finishd_eating == philos[0].nbr_of_philos)
    {
        pthread_mutex_lock(philos[0].dead_lock);
        *philos->dead = 1;
        pthread_mutex_unlock(philos[0].dead_lock);
        return (1);
    }
    return (0);
}

void    *thread_monitoring(void *pointer)
{
    t_philo *philos;
    
    philos = (t_philo *)pointer;
    while (1)
    {
        if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
            break;
        return (pointer);
    }
}