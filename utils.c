/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:58:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/01 13:36:38 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (sign * result);
}

long	currtime(void)
{
	t_timeval	result;

	if (gettimeofday(&result, NULL))
		ft_putendl_fd("Error getting current time.", STDOUT_FILENO);
	return (result.tv_sec * 1000 + result.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long	time;

	time = currtime();
	while (currtime() < time + ms)
		usleep(100);
}

int	isint(char *str, int *i)
{
	long	l;
	char	*p;

	p = str;
	if (*str == '-')
		str++;
	if (*str == '\0' || ft_strlen(str) > 10)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	l = ft_atol(p);
	if (l > 2147483 || l <= 0)
		return (0);
	if (i != NULL)
		*i = l;
	return (1);
}

void	putlog(t_philosopher *philo, char *state)
{
	pthread_mutex_lock(&philo->data->mutex_locks[lock_print]);
	if (!is_end(philo->data))
	{
		ft_putnbr_fd(currtime() - philo->data->starttime, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putnbr_fd(philo->pos + 1, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putendl_fd(state, STDOUT_FILENO);
	}
	pthread_mutex_unlock(&philo->data->mutex_locks[lock_print]);
}
