/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:28:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/29 14:26:10 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	tt_forks(t_philosopher *philo)
{
	long	forks_av;
	int		left;
	int		right;

	left = philo->pos - 1;
	right = philo->pos + 1;
	if (left < 0)
		left = philo->data->nop - 1;
	if (right == philo->data->nop)
		right = 0;
	forks_av = max(((t_philosopher *)philo->data->philos)[left].last_meal_end,
			((t_philosopher *)philo->data->philos)[right].last_meal_end);
	forks_av = max(forks_av, philo->event_end);
	if (forks_av < 0)
		forks_av += 1;
	return (forks_av);
}

static int	check_forks(t_philosopher *philo)
{
	int	left;
	int	*forks;
	int	*queue;

	forks = philo->data->forks;
	queue = philo->data->forks_queue;
	if (philo->pos == 0)
		left = philo->data->nop - 1;
	else
		left = philo->pos - 1;
	if (forks[left] == AVAILABLE && (queue[left] == AVAILABLE
			|| queue[left] == philo->pos) && forks[philo->pos] == AVAILABLE
		&& (queue[philo->pos] == AVAILABLE || queue[philo->pos] == philo->pos))
	{
		putlog(philo->event_end, philo, "has taken a fork");
		forks[left] = TAKEN;
		queue[left] = AVAILABLE;
		putlog(philo->event_end, philo, "has taken a fork");
		forks[philo->pos] = TAKEN;
		queue[philo->pos] = AVAILABLE;
		return (1);
	}
	queue[left] = philo->pos;
	queue[philo->pos] = philo->pos;
	return (0);
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
