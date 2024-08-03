/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:41:48 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/03 17:51:48 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_think(t_philosopher *philo)
{
	putlog(philo, "is thinking");
}

static void	start_sleep(t_philosopher *philo)
{
	putlog(philo, "is sleeping");
	set_times_eaten(philo);
	if (philo->data->tme != -1)
		check_times_eaten(philo->data);
	ft_usleep(philo->data->tts);
}

static void	get_fork_order(t_philosopher *philo, int *first, int *second)
{
	int	right;

	right = philo->pos - 1;
	if (right < 0)
		right = philo->data->nop - 1;
	if (philo->pos % 2 == 0 && philo->pos != philo->data->nop - 1)
	{
		*first = philo->pos;
		*second = right;
	}
	else
	{
		*first = right;
		*second = philo->pos;
	}
}

static void	start_eat(t_philosopher *philo)
{
	int	first;
	int	second;

	get_fork_order(philo, &first, &second);
	pthread_mutex_lock(&philo->data->fork_locks[first]);
	putlog(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork_locks[second]);
	putlog(philo, "has taken a fork");
	putlog(philo, "is eating");
	set_meal_start(philo, currtime());
	ft_usleep(philo->data->tte);
	pthread_mutex_unlock(&philo->data->fork_locks[second]);
	pthread_mutex_unlock(&philo->data->fork_locks[first]);
}

void	*init_events(void *v)
{
	t_philosopher	*philo;

	philo = v;
	while (!is_end(philo->data))
	{
		start_think(philo);
		if (philo->data->nop == 1)
		{
			ft_usleep(philo->data->ttd + 1);
			break ;
		}
		start_eat(philo);
		start_sleep(philo);
	}
	return (v);
}
