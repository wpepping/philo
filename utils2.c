/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:55:32 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/30 16:18:13 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->mutex_locks[lock_end]);
	result = data->end;
	pthread_mutex_unlock(&data->mutex_locks[lock_end]);
	return (result);
}

void	set_end(t_data *data)
{
	pthread_mutex_lock(&data->mutex_locks[lock_end]);
	data->end = 1;
	pthread_mutex_unlock(&data->mutex_locks[lock_end]);
}

long	get_meal_start(t_philosopher *philo)
{
	long	result;

	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	result = philo->last_meal_start;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
	return (result);
}

void	set_meal_start(t_philosopher *philo, long ctime)
{
	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	philo->last_meal_start = ctime;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
}

void	init_philos(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		philos[i].pos = i;
		philos[i].times_eaten = 0;
		philos[i].last_meal_start = data->starttime;
		philos[i].data = data;
		i++;
	}
}
