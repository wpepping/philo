/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:32:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/29 14:29:59 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"

enum e_philo_states {IDLE, THINKING, EATING, SLEEPING, DEAD};
enum e_mutex_locks {LOCK_FORKS, LOCK_PRINT, LOCK_DIE, LOCK_EAT};

# define AVAILABLE 0
# define TAKEN 1
# define NR_OF_LOCKS 4

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				tme;
	int				end;
	long			starttime;
	int				*forks;
	int				*forks_queue;
	void			*philos;
	pthread_mutex_t	*mutex_locks;
	pthread_mutex_t	*fork_locks;
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
long	tt_forks(t_philosopher *philo);
int		forks_available(t_philosopher *philo);
long	currtime(void);
void	init_philo(t_philosopher *philo, int i, t_data *data);
int		*init_forks(int n);
int		isint(char *str, int *i);
long	ft_atol(const char *nptr);
int		min(int a, int b);
long	max(long a, long b);
void	putlog(long ctime, t_philosopher *philo, char *state);
int		mutex_destroy(t_data *data, int n);
int		mutex_init(t_data *data);

#endif
