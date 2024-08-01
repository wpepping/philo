/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:32:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/08/01 13:27:54 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>

enum e_mutex_locks {lock_forks, lock_print, lock_end};

# define NR_OF_LOCKS 4

typedef struct timeval			t_timeval;
typedef struct s_philosopher	t_philosopher;

typedef struct s_data
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				tme;
	int				end;
	long			starttime;
	t_philosopher	*philos;
	pthread_mutex_t	*mutex_locks;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	*meal_locks;
}	t_data;

typedef struct s_philosopher
{
	int				pos;
	int				times_eaten;
	long			last_meal_start;
	t_data			*data;
	pthread_t		thread_id;
}	t_philosopher;

// Libft functions
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long n, int fd);

// Other functions
long	currtime(void);
void	init_philos(t_philosopher *philos, t_data *data);
int		isint(char *str, int *i);
long	ft_atol(const char *nptr);
void	putlog(t_philosopher *philo, char *state);
int		mutex_init(t_data *data);
int		mutex_destroy(t_data *data, int n, int forks_done);
void	*init_events(void *v);
int		is_end(t_data *data);
void	set_end(t_data *data);
long	get_meal_start(t_philosopher *philo);
void	set_meal_start(t_philosopher *philo, long ctime);
void	ft_usleep(int milliseconds);
void	init_threads(t_philosopher *philos, t_data *data);
void	join_threads(t_philosopher *philos, t_data *data);
int		error_handl(char *message, t_data *data);

#endif
