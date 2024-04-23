/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:30:31 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/04/23 20:04:56 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *decider(void *philo)
{
	eating(philo);
	sleeping(philo);
	thinking(philo);
	return (NULL);
}

void eating(t_philo *philo)
{
	struct				timeval time;
	long long			time_stamp;

	usleep(philo -> time_to_eat);
	gettimeofday(&time, NULL);
	time_stamp = (time.tv_sec * 1000 + time.tv_usec / 1000) - 
			philo -> start_time;
	printf("%lli %i is eating\n", time_stamp, philo -> id);
}

void sleeping(t_philo *philo)
{
	struct				timeval time;
	long long			time_stamp;

	usleep(philo -> time_to_sleep);
	gettimeofday(&time, NULL);
	time_stamp = (time.tv_sec * 1000 + time.tv_usec / 1000) - 
			philo -> start_time;
	printf("%lli %i is sleeping\n", time_stamp, philo -> id);
}

void thinking(t_philo *philo)
{
	struct				timeval time;
	long long			time_stamp;

	gettimeofday(&time, NULL);
	time_stamp = (time.tv_sec * 1000 + time.tv_usec / 1000) - 
			philo -> start_time;
	printf("%lli %i is thinking\n", time_stamp, philo -> id);
}