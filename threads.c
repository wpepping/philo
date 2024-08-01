/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:13:26 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/01 13:35:24 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_philosopher *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nop)
	{
		if (pthread_create(&philos[i].thread_id, NULL, init_events, &philos[i]))
			error_handl("Thread creation failed.\n", data);
	}
}

void	join_threads(t_philosopher *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(philos[i].thread_id, NULL))
			error_handl("Thread join failed.\n", data);
	}
}
