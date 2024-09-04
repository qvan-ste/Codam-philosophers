/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 18:17:29 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 19:48:59 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	cleanup(t_global global)
{
	size_t	i;

	i = 0;
	if (global.philos != NULL)
		free(global.philos);
	if (global.forks != NULL)
		free(global.forks);
	pthread_mutex_destroy(&global.print_lock);
	pthread_mutex_destroy(&global.status_lock);
	while (i < global.num_of_philos)
	{
		pthread_mutex_destroy(&global.philos[i].eating);
		pthread_mutex_destroy(&global.forks[i]);
		i++;
	}
}

void	join_threads(t_global global)
{
	size_t	i;

	i = 0;
	while (i < global.num_of_philos)
	{
		pthread_join(global.philos[i].thread_id, NULL);
		i++;
	}
}

int	create_threads(t_global *global)
{
	size_t		i;
	pthread_t	observer;

	i = 0;
	if (pthread_create(&observer, NULL, check_status, global) == -1)
		return (-1);
	while (i < global -> num_of_philos)
	{
		if (pthread_create(&global -> philos[i].thread_id,
				NULL, start_simulation, &global -> philos[i]) == -1)
			return (-1);
		i++;
	}
	pthread_mutex_lock(&global -> status_lock);
	global -> start_time = get_time();
	global -> status = RUNNING;
	pthread_mutex_unlock(&global -> status_lock);
	pthread_join(observer, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_global	global;
	int			ret;


	if (check_input(argc, argv) != 0)
		return (1);
	if (init_global(&global, argv) != 0)
		return (1);
	if (global.num_of_philos == 1)
	{
		philo_sleep(global.time_to_die);
		printf("%i 1 died\n", global.time_to_die);
		return (0);
	}
	if (init_mutexes(&global) != 0)
		return (cleanup(global), 1);
	if (init_philos(&global) != 0)
		return (cleanup(global), 1);
	ret = create_threads(&global);
	join_threads(global);
	cleanup(global);
	return (ret);
}
