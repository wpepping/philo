/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:32:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/22 17:51:20 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DEAD 3
# define AVAILABLE 0
# define TAKEN 1

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				tme;
	int				philodied;
	long			starttime;
	int				*forks;
	void			*philos;
	pthread_mutex_t	forklock;
	pthread_mutex_t	printlock;
	pthread_mutex_t	dielock;
}	t_data;

typedef struct s_philosopher
{
	int				pos;
	int				state;
	int				times_eaten;
	long			event_end;
	long			last_meal_end;
	t_data			*data;
	pthread_t		thread_id;
}	t_philosopher;

void	try_eat(t_philosopher *philo);
int		forks_available(t_philosopher *philo);
long	currtime();
void	init_philo(t_philosopher *philo, int i, t_data *data);
int		*init_forks(int n);
int		isint(char *str, int *i);
long	ft_atol(const char *nptr);
int		min(int a, int b);
int		max(int a, int b);
void	putlog(long ctime, t_philosopher *philo, char *state);

#endif
