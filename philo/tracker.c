/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 13:14:17 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 15:32:55 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	all_ate(t_global *global)
{
	size_t		i;

	i = 0;
	if (global -> num_should_eat < 0)
		return (false);
	while (i < global -> num_of_philos)
	{
		pthread_mutex_lock(&global->philos[i].eating);
		if (global->philos[i].num_eaten < global -> num_should_eat)
		{
			pthread_mutex_unlock(&global->philos[i].eating);
			return (false);
		}
		pthread_mutex_unlock(&global->philos[i].eating);
		i++;
	}
	pthread_mutex_lock(&global-> status_lock);
	global -> status = END;
	pthread_mutex_unlock(&global-> status_lock);
	return (true);
}

bool	philo_died(t_global *global)
{
	size_t		i;
	long long	timestamp;

	i = 0;
	while (i < global->num_of_philos)
	{
		pthread_mutex_lock(&global->philos[i].eating);
		if (now() - global->philos[i].time_last_eaten > global->time_to_die)
		{
			pthread_mutex_unlock(&global->philos[i].eating);
			print_action(global, global->philos[i].id, "died");
			pthread_mutex_lock(&global->status_lock);
			global->status = END;
			pthread_mutex_unlock(&global->status_lock);
			return (true);
		}
		pthread_mutex_unlock(&global->philos[i].eating);
		i++;
	}
	return (false);
}

void	*track_philosophers(void *data)
{
	t_global	*global;

	global = data;
	while (1)
	{
		pthread_mutex_lock(&global ->status_lock);
		if (global -> status == RUNNING)
			break ;
		pthread_mutex_unlock(&global-> status_lock);
	}
	pthread_mutex_unlock(&global-> status_lock);
	while (!philo_died(global) && !all_ate(global))
	{
		usleep(500);
	}
	return (NULL);
}
