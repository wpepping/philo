/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:13:26 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/03 17:55:05 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philosopher *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nop)
	{
		philos[i].last_meal_start = data->starttime;
		if (pthread_create(&philos[i].thread_id, NULL, init_events, &philos[i]))
			return (error_handl("Thread creation failed.\n", data));
	}
	return (0);
}

int	join_threads(t_philosopher *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(philos[i].thread_id, NULL))
			return (error_handl("Thread join failed.\n", data));
	}
	return (0);
}
