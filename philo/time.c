/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 12:36:03 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 20:16:09 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Time error\n");
		return (-1);
	}
	return (1000000 * time.tv_sec + time.tv_usec);
}

int time_passed(long long start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Time error\n");
		return (-1);
	}
	return (get_time() / 1000 - start_time / 1000);
}


void	philo_sleep(int duration)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < duration * 1000)
		usleep(50);
}

void	sync_start(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo -> global -> status_lock);
		if (philo->global->status != INIT)
		{
			pthread_mutex_unlock(&philo -> global -> status_lock);
			pthread_mutex_lock(&philo -> eating);
			philo -> time_last_eaten = philo -> global-> start_time;
			pthread_mutex_unlock(&philo -> eating);
			break ;
		}
		pthread_mutex_unlock(&philo -> global -> status_lock);
	}
	if (philo -> id % 2 == 0)
		usleep(1500);
}
