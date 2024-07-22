/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:55:32 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/22 20:28:27 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *philo, int i, t_data *data)
{
	philo->pos = i;
	philo->state = IDLE;
	philo->times_eaten = 0;
	philo->event_end = data->starttime;
	philo->last_meal_end = data->starttime;
	philo->data = data;
}

int	*init_forks(int n)
{
	int	*result;
	int	i;

	result = malloc(n * sizeof(int));
	i = 0;
	while (i < n)
		result[i++] = AVAILABLE;
	return (result);
}

void	putlog(long ctime, t_philosopher *philo, char *state)
{
	pthread_mutex_lock(&philo->data->mutex_locks[LOCK_PRINT]);
	if (!philo->data->end)
	{
		ft_putnbr_fd(ctime - philo->data->starttime, STDOUT_FILENO);
		ft_putstr_fd(" philosopher ", STDOUT_FILENO);
		ft_putnbr_fd(philo->pos, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putendl_fd(state, STDOUT_FILENO);
	}
	pthread_mutex_unlock(&philo->data->mutex_locks[LOCK_PRINT]);
}

