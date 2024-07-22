/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:56:01 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/22 20:43:17 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_destroy(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&data->mutex_locks[i++]);
	free(data->mutex_locks);
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	data->mutex_locks = malloc(NR_OF_LOCKS * sizeof(pthread_mutex_t));
	i = 0;
	while (i < NR_OF_LOCKS)
	{
		if (pthread_mutex_init(&data->mutex_locks[i], NULL) != 0)
			return (mutex_destroy(data, i));
		i++;
	}
	return (1);
}
