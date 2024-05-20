/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:26 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/20 21:57:16 by quincy        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

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

void join_threads(pthread_t tracker, t_philo *philos)
{
	t_philo		*head;

	head = philos;
	pthread_join(tracker, NULL);
	head = philos;
	while (1)
	{
		pthread_join(philos -> thread_id, NULL);
		philos = philos -> next;
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
		return (1);
	while (1)
	{
		if (pthread_create(&philos -> thread_id, NULL, start_simulation, philos) == -1)
			return (1);
		philos = philos -> next;
		if (philos == head)
			break ;
	}
	join_threads(tracker, philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	int			exit;

	if (check_input(argc, argv) != 0)
		return (1);
	if (ft_atoi(argv[1]) == 1)
	{
		usleep(ft_atoi(argv[2]));
		printf("%i 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	philos = create_philosophers(argv);
	if (!philos)
		return (1);
	exit = create_threads(philos);
	free_global(philos -> global);
	free_philos(philos);
	return (exit);
}
