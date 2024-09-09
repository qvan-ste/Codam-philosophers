/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 12:36:03 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/09 17:47:25 by qvan-ste      ########   odam.nl         */
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
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	time_passed(long long start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Time error\n");
		return (-1);
	}
	return (get_time() - start_time);
}

void	philo_sleep(int duration)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	while (1)
	{
		current_time = get_time();
		if ((current_time - start_time) >= duration)
			break ;
		usleep(100);
	}
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
	{
		print_action(philo -> global, philo -> id, "is thinking");
		usleep(1500);
	}
}
