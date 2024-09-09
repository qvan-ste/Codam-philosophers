/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 13:14:17 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/09 15:11:52 by qvan-ste      ########   odam.nl         */
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

	i = 0;
	while (i < global -> num_of_philos)
	{
		pthread_mutex_lock(&global->philos[i].eating);
		if (get_time() - global->philos[i].time_last_eaten
			>= global -> time_to_die)
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

bool	end_of_sim(t_global *global)
{
	bool	result;

	pthread_mutex_lock(&global->status_lock);
	result = (global->status == END);
	pthread_mutex_unlock(&global->status_lock);
	return (result);
}

void	*check_status(void *data)
{
	t_global	*global;

	global = data;
	while (1)
	{
		pthread_mutex_lock(&global ->status_lock);
		if (global -> status != INIT)
			break ;
		pthread_mutex_unlock(&global-> status_lock);
		usleep(100);
	}
	pthread_mutex_unlock(&global-> status_lock);
	while (!end_of_sim(global))
	{
		if (philo_died(global) || all_ate(global))
			break ;
		usleep(5000);
	}
	return (NULL);
}
