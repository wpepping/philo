/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:57 by wpepping          #+#    #+#             */
/*   Updated: 2024/07/13 16:48:21 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	counter;

void	*my_thread(void *vargp)
{
	counter += 1;
	printf("\n Job %d has started\n", counter);
	sleep(1);
	printf("\n Job %d has finished\n", counter);
	return (vargp);
}

int	main(void)
{
	pthread_t	thread_id;

	printf("Before Threads\n");
	pthread_create(&thread_id, NULL, my_thread, NULL);
	pthread_create(&thread_id, NULL, my_thread, NULL);
	pthread_join(thread_id, NULL);
	pthread_join(thread_id, NULL);
	printf("After Threads\n");
	return (0);
}
