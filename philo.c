/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:57 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/29 12:59:08 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*init_events(void *v)
{
	try_eat(v);
	return (v);
}

static int	validate_input(int argc, char **argv, t_data *data)
{
	data->tme = -1;
	if (argc == 5)
	{
		if (isint(argv[1], &data->nop) && isint(argv[2], &data->ttd)
			&& isint(argv[3], &data->tte) && isint(argv[4], &data->tts))
			return (1);
	}
	else if (argc == 6)
	{
		if (isint(argv[1], &data->nop) && isint(argv[2], &data->ttd)
			&& isint(argv[3], &data->tte) && isint(argv[4], &data->tts)
			&& isint(argv[5], &data->tme))
			return (1);
	}
	return (0);
}

static int	error_handl(char *message, t_data *data)
{
	ft_putendl_fd(message, STDERR_FILENO);
	data->end = 1;
	return (1);
}

static int	init(int argc, char **argv, t_data *data, t_philosopher **philos)
{
	if (!validate_input(argc, argv, data))
		return (error_handl("Invalid arguments.\n", data));
	if (!mutex_init(data))
		return (error_handl("Mutex init failed.\n", data));
	*philos = malloc(data->nop * sizeof(t_philosopher));
	data->philos = *philos;
	data->forks = init_forks(data->nop);
	data->forks_queue = init_forks(data->nop);
	data->starttime = currtime();
	data->end = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philos;
	int				i;
	int				result;

	if (init(argc, argv, &data, &philos))
		return (1);
	result = 0;
	i = -1;
	while (++i < data.nop)
	{
		init_philo(&philos[i], i, &data);
		if (pthread_create(&philos[i].thread_id, NULL, init_events, &philos[i]))
			result = error_handl("Thread creation failed.\n", &data);
	}
	i = 0;
	while (i < data.nop)
	{
		if (pthread_join(philos[i++].thread_id, NULL))
			result = error_handl("Thread join failed.\n", &data);
	}
	mutex_destroy(&data, NR_OF_LOCKS);
	free(philos);
	free(data.forks);
	return (result);
}
