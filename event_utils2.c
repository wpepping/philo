/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:37:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/03 17:50:16 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_meal_start(t_philosopher *philo)
{
	long	result;

	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	result = philo->last_meal_start;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
	return (result);
}

int	get_times_eaten(t_philosopher *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	result = philo->times_eaten;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
	return (result);
}

void	set_meal_start(t_philosopher *philo, long ctime)
{
	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	philo->last_meal_start = ctime;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
}

void	set_times_eaten(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->meal_locks[philo->pos]);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->meal_locks[philo->pos]);
}
