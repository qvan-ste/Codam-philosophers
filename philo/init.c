/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:53:51 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/04/23 20:05:49 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philosopher(int argc, char*argv[], int id)
{
	t_philo		*philo;
	struct		timeval time;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo -> id = id + 1;
	philo -> start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	philo -> num_of_philosophers = ft_atoi(argv[1]);
	philo -> time_to_die = ft_atoi(argv[2]);
	philo -> time_to_eat = ft_atoi(argv[3]);
	philo -> time_to_sleep = ft_atoi(argv[4]);
	if (argc ==	6 )
		philo -> num_should_eat = ft_atoi(argv[5]);
	else
	 	philo -> num_should_eat = 0;
	return(philo);
}

t_listdoub	*create_philosophers(int argc, char*argv[])
{
	t_listdoub	*head;
	t_listdoub	*node;
	t_philo		*philosopher;
	int			i;
	
	i = 1;
	philosopher = init_philosopher(argc, argv, 0);
	if (!philosopher)
		return (NULL);	
	head = ft_lstdoubnew(philosopher);
	if (!head)
		return (NULL);
	while (i < ft_atoi(argv[1]))
	{
		philosopher = init_philosopher(argc, argv , i);
		if (!philosopher)
			return (NULL);
		node = ft_lstdoubnew(philosopher);
		if (!node)
			return (NULL);
		ft_lstdoubadd_back(&head, node);
		i++;
	}
	return (head);
}
