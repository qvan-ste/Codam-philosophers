/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:26 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/04/23 20:02:18 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_listdoub *philosophers)
{
	int			i;
	int			num;
	pthread_t	thread_id;
	t_philo		*philo;
	
	i = 0;
	num = philosophers -> philo -> num_of_philosophers;
	while (i < num)
	{
		philo = philosophers -> philo;
		if (pthread_create(&thread_id, NULL , decider, philo) == -1)
			return (-1);
		philo -> thread_id = thread_id;
		pthread_join(thread_id, NULL);
		philosophers = philosophers -> next;
		i++;
	}
	return (0);
}

int main (int argc, char *argv[])
{
	t_listdoub	*philosophers;
	int			i = 0;
	
	if (argc != 5 && argc != 6)
		return (1);
	philosophers = create_philosophers(argc, argv);
	if (!philosophers)
		return (1);
	if (create_threads(philosophers) == -1)
		return (1);
}