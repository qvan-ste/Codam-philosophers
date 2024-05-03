/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:26 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/03 19:13:00 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_global(t_global	*global)
{
	pthread_mutex_destroy(&global -> print_lock);
	pthread_mutex_destroy(&global -> death_lock);
	pthread_mutex_destroy(&global -> ate_lock);
	free(global);
}

void free_philos(t_philo *philos)
{
	t_philo 	*head;
	t_philo		*tmp;

	head = philos;
	while (1)
	{
		if (!philos)
			return ;
		pthread_mutex_destroy(&philos -> eating);
		pthread_mutex_destroy(&philos -> fork_in_use);
		tmp = philos;
		philos = philos -> next;
		free(tmp);
		if (philos == head)
			break ;
	}
}

int	create_threads(t_philo *philos)
{
	t_philo		*head;
	pthread_t	tracker;

	head = philos;
	if (pthread_create(&tracker, NULL, track_philosophers, philos) == -1)
		return (-1);
	while (1)
	{
		if (pthread_create(&philos -> thread_id, NULL, start_simulation, philos) == -1)
			return (-1);
		pthread_detach(philos -> thread_id);
		philos = philos -> next;
		if (philos == head)
			break ;
	}
	pthread_join(tracker, NULL);
	usleep(10000);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;

	check_input(argc, argv);
	philos = create_philosophers(argv);
	if (!philos)
		return (1);
	if (create_threads(philos) == -1)
		return (1);
	free_global(philos -> global);
	free_philos(philos);
}
