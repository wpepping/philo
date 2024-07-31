/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:57 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/31 21:01:52 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philos == NULL)
		return (error_handl("Memory allocation failed.\n", data));
	data->philos = *philos;
	data->end = 0;
	data->starttime = currtime();
	return (0);
}

static void	check_deaths(t_philosopher *philos, t_data *data)
{
	int	i;

	while (!is_end(data))
	{
		i = 0;
		while (i < data->nop)
		{
			if (currtime() - get_meal_start(&philos[i]) - 1 >= data->ttd)
			{
				putlog(&philos[i], "has died");
				set_end(data);
			}
			i++;
		}
		ft_usleep(1);
	}
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
	init_philos(philos, &data);
	i = -1;
	while (++i < data.nop)
	{
		if (pthread_create(&philos[i].thread_id, NULL, init_events, &philos[i]))
			result = error_handl("Thread creation failed.\n", &data);
	}
	check_deaths(philos, &data);
	i = -1;
	while (++i < data.nop)
	{
		if (pthread_join(philos[i].thread_id, NULL))
			result = error_handl("Thread join failed.\n", &data);
	}
	mutex_destroy(&data, data.nop, 2);
	free(philos);
	return (result);
}
