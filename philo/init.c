/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:53:51 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/06/03 19:24:49 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global *init_global(char *argv[])
{
	t_global		*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return  (NULL);
	// global -> queue = malloc(100000000);
	memset(global, 0, sizeof(t_global));
	pthread_mutex_init(&global -> print_lock, NULL);
	pthread_mutex_init(&global -> death_lock, NULL);
	pthread_mutex_init(&global -> ate_lock, NULL);
	pthread_mutex_init(&global -> queue_lock, NULL);
	return (global);
}

t_philo	*philo_new(char*argv[], int id, long long start_time, t_global *global)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo -> id = id + 1;
	philo -> start_time = start_time;
	philo -> num_of_philos = ft_atoi(argv[1]);
	philo -> time_to_die = ft_atoi(argv[2]);
	philo -> time_to_eat = ft_atoi(argv[3]);
	philo -> time_to_sleep = ft_atoi(argv[4]);
	philo -> time_last_eaten = start_time;
	if (argv[5])
		philo -> num_should_eat = ft_atoi(argv[5]);
	else
		philo -> num_should_eat = 0;
	pthread_mutex_init(&philo -> eating, NULL);
	pthread_mutex_init(&philo -> fork_in_use, NULL);
	philo -> next = NULL;
	philo -> global = global;
	return (philo);
}

void	philoadd_back(t_philo **head, t_philo *new)
{
	t_philo	*current;

	current = *head;
	if (!(*head)-> next)
	{
		(*head)-> next = new;
		new -> next = *head;
	}
	else
	{
		while (current -> next != *head)
			current = current->next;
		current -> next = new;
		new -> next = *head;
	}
}

t_philo	*create_philosophers(char*argv[])
{
	t_philo			*head;
	t_philo			*node;
	t_global		*global;
	long long		start_time;
	int				i;

	global = init_global(argv);
	if (!global)
		return (NULL);
	start_time = now();
	i = 1;
	head = philo_new(argv, 0, start_time, global);
	if (!head)
		return (free_global(global), NULL);
	while (i < ft_atoi(argv[1]))
	{
		node = philo_new(argv, i, start_time, global);
		if (!node)
			return (free_philos(head), free_global(global), NULL);
		philoadd_back(&head, node);
		i++;
	}
	return (head);
}
