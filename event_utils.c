/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:55:32 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/03 17:54:54 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		philos[i].pos = i;
		philos[i].times_eaten = 0;
		philos[i].data = data;
		i++;
	}
}

void	check_times_eaten(t_data *data)
{
	int	i;
	int	philos_done_eating;

	philos_done_eating = 0;
	i = 0;
	while (i < data->nop)
	{
		if (get_times_eaten(&data->philos[i]) >= data->tme)
			philos_done_eating++;
		i++;
	}
	if (philos_done_eating == data->nop)
		set_end(data);
}

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
