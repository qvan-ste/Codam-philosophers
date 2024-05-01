/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:30:31 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 19:35:26 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*action(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo -> fork_in_use);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo -> next -> fork_in_use);
	print_action(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	philo -> is_eating = 1;
	print_action(philo, "is eating");
	usleep(philo -> time_to_eat);
	philo -> time_last_eaten = now();
	philo -> num_eaten++;
	philo -> is_eating = 0;
	pthread_mutex_unlock(&philo -> fork_in_use);
	pthread_mutex_unlock(&philo -> next -> fork_in_use);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo -> time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}
