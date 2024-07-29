/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:41:48 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/29 13:38:24 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_think(t_philosopher *philo)
{
	long	think_end;
	long	forks_av;

	forks_av = tt_forks(philo);
	if (forks_av > philo->last_meal_end + philo->data->ttd)
		think_end = philo->last_meal_end + philo->data->ttd;
	else
		think_end = forks_av;
	if (philo->state != THINKING)
		putlog(philo->event_end, philo, "is thinking");
	philo->state = THINKING;
	philo->event_end = think_end;
	usleep(max((think_end - currtime() * 1000), 1));
}

static void	start_sleep(t_philosopher *philo)
{
	int	left;

	if (philo->pos == 0)
		left = philo->data->nop - 1;
	else
		left = philo->pos - 1;
	philo->data->forks[left] = AVAILABLE;
	philo->data->forks[philo->pos] = AVAILABLE;
	philo->state = SLEEPING;
	putlog(philo->event_end, philo, "is sleeping");
	philo->event_end += min(philo->data->tts, philo->data->ttd);
	usleep((philo->event_end - currtime()) * 1000);
}

static void	start_eat(t_philosopher *philo)
{
	putlog(philo->event_end, philo, "is eating");
	philo->times_eaten++;
	if (philo->data->tme != -1 && philo->times_eaten > philo->data->tme)
		philo->data->end = 1;
	philo->state = EATING;
	philo->event_end += philo->data->tte;
	philo->last_meal_end = philo->event_end;
	usleep((philo->event_end - currtime()) * 1000);
	start_sleep(philo);
}

static void	died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->mutex_locks[LOCK_DIE]);
	putlog(philo->last_meal_end + philo->data->ttd, philo, "died");
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->mutex_locks[LOCK_DIE]);
	philo->state = DEAD;
}

void	try_eat(t_philosopher *philo)
{
	while (!philo->data->end)
	{
		if (philo->state != IDLE && philo->state != EATING
			&& philo->last_meal_end + philo->data->ttd <= philo->event_end)
			died(philo);
		else if (forks_available(philo))
			start_eat(philo);
		else
			start_think(philo);
	}
}
