/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:55:32 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/22 17:19:30 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philosopher *philo, int i, t_data *data)
{
	philo->pos = i;
	philo->state = EATING;
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
	pthread_mutex_lock(&philo->data->printlock);
	if (!philo->data->philodied)
	{
		ft_putnbr_fd(ctime - philo->data->starttime, STDOUT_FILENO);
		ft_putstr_fd(" philosopher ", STDOUT_FILENO);
		ft_putnbr_fd(philo->pos, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putendl_fd(state, STDOUT_FILENO);
	}
	pthread_mutex_unlock(&philo->data->printlock);
}

int	forks_available(t_philosopher *philo)
{
	int		left;
	int		result;
	int		*forks;

	forks = philo->data->forks;
	if (philo->pos == 0)
		left = philo->data->nop - 1;
	else
		left = philo->pos - 1;
	pthread_mutex_lock(&philo->data->forklock);
	if (forks[left] == AVAILABLE && forks[philo->pos] == AVAILABLE)
	{
		forks[left] = TAKEN;
		forks[philo->pos] = TAKEN;
		result = 1;
	}
	else
		result = 0;
	pthread_mutex_unlock(&philo->data->forklock);
	return (result);
}
