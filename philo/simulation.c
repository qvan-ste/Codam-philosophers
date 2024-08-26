/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:30:31 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/08/26 17:36:36 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_simulation(void *data)
{
	t_philo	*philo;

	philo = data;
	while(!philo -> global -> start_time)
		continue;
	philo -> time_last_eaten = philo -> global -> start_time;
	if (philo ->id % 2 == 0)
		philo_sleep(philo -> time_to_eat);
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
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo -> next -> fork_in_use);
		print_action(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo -> eating);
	print_action(philo, "is eating");
	philo -> time_last_eaten = now();
	philo_sleep(philo -> time_to_eat);
	philo -> num_eaten++;
	pthread_mutex_unlock(&philo -> fork_in_use);
	pthread_mutex_unlock(&philo -> next -> fork_in_use);
	pthread_mutex_unlock(&philo -> eating);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	philo_sleep(philo -> time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}
