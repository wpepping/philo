/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:28:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/23 13:40:57 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	tt_forks(t_philosopher *philo)
{
	int				i;
	long			result;
	t_philosopher	*philos;

	philos = (t_philosopher *)philo->data->philos;
	result = philo->event_end + philo->data->tte;
	i = 0;
	while (i < philo->data->nop)
	{
		if (philos[i].state == EATING)
		{
			if (result == -1 || philos[i].event_end < result)
				result = philos[i].event_end;
		}
		i++;
	}
	return (result);
}

static int	check_forks(t_philosopher *philo)
{
	int		left;
	int		result;
	int		*forks;

	forks = philo->data->forks;
	if (philo->pos == 0)
		left = philo->data->nop - 1;
	else
		left = philo->pos - 1;
	if (forks[left] == AVAILABLE && forks[philo->pos] == AVAILABLE)
	{
		putlog(philo->event_end, philo, "has taken a fork");
		forks[left] = TAKEN;
		putlog(philo->event_end, philo, "has taken a fork");
		forks[philo->pos] = TAKEN;
		result = 1;
	}
	else
		result = 0;
	return (result);
}

int	forks_available(t_philosopher *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->mutex_locks[LOCK_FORKS]);
	result = check_forks(philo);
	while (!result && tt_forks(philo) == philo->event_end)
	{
		usleep(1);
		result = check_forks(philo);
	}
	pthread_mutex_unlock(&philo->data->mutex_locks[LOCK_FORKS]);
	return (result);
}
