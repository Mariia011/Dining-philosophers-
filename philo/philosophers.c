/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/05/27 17:01:04 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int count = 0;
pthread_mutex_t mutex;

void *foo(void * data)
{
	unsigned long * p = (unsigned long*)data;
	for(unsigned long i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		count++;
		usleep(10000);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
#ifdef PHILOS
#define PHILOS 3
#endif
int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_t philosopher[PHILOS];

	for (int i = 0; i < PHILOS; i++)
	{
		if(pthread_create(philosopher + i, NULL, &foo, &i) != 0)
			return 0;
		printf("thread %d is opened\n", i);
	}
	for (int i = 0; i < PHILOS; i++)
	{
		if(pthread_join(philosopher[i], NULL) != 0)
			return 0;
		printf("thread %d is closed\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("the count is %u \n", count);
	return 0;
}
