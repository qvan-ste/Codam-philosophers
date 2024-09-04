/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 12:36:03 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 15:34:01 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

long long	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Time error\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_sleep(int duration)
{
	long long	start_time;
	long long	elapsed_time;

	start_time = now();
	if (start_time == -1)
		return ;
	while (1)
	{
		elapsed_time = now() - start_time;
		if (elapsed_time >= duration)
			break ;
		usleep(100);
	}
}

void	sync_start(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->global->status_lock);
		if (philo->global->status != INIT)
		{
			pthread_mutex_unlock(&philo->global->status_lock);
			pthread_mutex_lock(&philo->eating);
			philo->time_last_eaten = philo->global->start_time;
			pthread_mutex_unlock(&philo->eating);
			break ;
		}
		pthread_mutex_unlock(&philo->global->status_lock);
		usleep(100);
	}
	if (philo->id % 2 == 0)
		philo_sleep(5);
}
