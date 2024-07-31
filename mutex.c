/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:56:01 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/30 16:33:17 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_locks(pthread_mutex_t *locks, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&locks[i++]);
	free(locks);
}

int	mutex_destroy(t_data *data, int n, int locks_done)
{
	if (locks_done == 0)
	{
		destroy_locks(data->mutex_locks, n);
	}
	else if (locks_done == 1)
	{
		destroy_locks(data->mutex_locks, NR_OF_LOCKS);
		destroy_locks(data->fork_locks, n);
	}
	else if (locks_done == 2)
	{
		destroy_locks(data->mutex_locks, NR_OF_LOCKS);
		destroy_locks(data->fork_locks, data->nop);
		destroy_locks(data->meal_locks, n);
	}
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	data->mutex_locks = malloc(NR_OF_LOCKS * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < NR_OF_LOCKS)
	{
		if (pthread_mutex_init(&data->mutex_locks[i], NULL) != 0)
			return (mutex_destroy(data, i, 0));
	}
	data->fork_locks = malloc(data->nop * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->nop)
	{
		if (pthread_mutex_init(&data->fork_locks[i], NULL) != 0)
			return (mutex_destroy(data, i, 1));
	}
	data->meal_locks = malloc(data->nop * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->nop)
	{
		if (pthread_mutex_init(&data->meal_locks[i], NULL) != 0)
			return (mutex_destroy(data, i, 2));
	}
	return (1);
}
