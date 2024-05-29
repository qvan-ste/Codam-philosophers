/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:30:31 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/29 15:05:05 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_simulation(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!end_of_sim(philo))
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
	pthread_mutex_lock(&philo -> next -> fork_in_use);
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo -> eating);
	usleep(philo -> time_to_eat);
	philo -> time_last_eaten = now();
	philo -> num_eaten++;
	pthread_mutex_unlock(&philo -> fork_in_use);
	pthread_mutex_unlock(&philo -> next -> fork_in_use);
	pthread_mutex_unlock(&philo -> eating);
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
