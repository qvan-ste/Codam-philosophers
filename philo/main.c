/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:26 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 19:41:31 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo)
{
	t_philo		*head;
	pthread_t	tracker;

	head = philo;
	if (pthread_create(&tracker, NULL, track_philosophers, philo) == -1)
		return (-1);
	while (philo)
	{
		if (pthread_create(&philo -> thread_id, NULL, action, philo) == -1)
			return (-1);
		pthread_detach(philo -> thread_id);
		philo = philo -> next;
		if (philo == head)
			break ;
	}
	pthread_join(tracker, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philosophers;

	check_input(argc, argv);
	philosophers = create_philosophers(argv);
	if (!philosophers)
		return (1);
	if (create_threads(philosophers) == -1)
		return (1);
}
