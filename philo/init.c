/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 13:26:12 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/11 13:36:50 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

int	init_global(t_global *global, char **argv)
{
	size_t	i;

	i = 0;
	memset(global, 0, sizeof(t_global));
	global -> num_of_philos = ft_atoi(argv[1]);
	global -> time_to_die = ft_atoi(argv[2]);
	global -> time_to_eat = ft_atoi(argv[3]);
	global -> time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		global -> num_should_eat = ft_atoi(argv[5]);
	else
		global -> num_should_eat = -1;
	global -> forks = malloc(global -> num_of_philos * sizeof(pthread_mutex_t));
	if (!global -> forks)
		return (-1);
	global -> philos = malloc(global -> num_of_philos * sizeof(t_philo));
	if (!global -> philos)
	{
		free(global -> forks);
		return (-1);
	}
	return (0);
}

int	init_forks(t_global *global)
{
	size_t	i;

	i = 0;
	while (i < global -> num_of_philos)
	{
		if (pthread_mutex_init(&global -> forks[i], NULL) == -1)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&global -> forks[i]);
			pthread_mutex_destroy(&global -> status_lock);
			pthread_mutex_destroy(&global -> print_lock);
			free(global -> forks);
			free(global -> philos);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_global_mutexes(t_global *global)
{
	int	ret;

	if (pthread_mutex_init(&global -> print_lock, NULL) == -1)
	{
		free(global -> forks);
		free(global -> philos);
		return (-1);
	}
	if (pthread_mutex_init(&global -> status_lock, NULL) == -1)
	{
		pthread_mutex_destroy(&global -> print_lock);
		free(global -> forks);
		free(global -> philos);
		return (-1);
	}
	ret = init_forks(global);
	return (ret);
}

int	init_eatlock(t_global *global)
{
	size_t	i;

	i = 0;
	while (i < global -> num_of_philos)
	{
		if (pthread_mutex_init(&global -> philos[i].eating, NULL) == -1)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&global -> philos[i].eating);
			while (i < global -> num_of_philos)
				pthread_mutex_destroy(&global -> forks[i++]);
			pthread_mutex_destroy(&global -> print_lock);
			pthread_mutex_destroy(&global -> status_lock);
			free(global -> forks);
			free(global -> philos);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_global *global)
{
	size_t	i;
	int		ret;

	i = 0;
	memset(global -> philos, 0, sizeof(t_philo));
	while (i < global -> num_of_philos)
	{
		global -> philos[i].id = i;
		global -> philos[i].global = global;
		global -> philos[i].time_last_eaten = get_time();
		global -> philos[i].l_fork = i;
		global -> philos[i].r_fork = (i + 1) % global -> num_of_philos;
		i++;
	}
	ret = init_eatlock(global);
	return (ret);
}
