/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:30:31 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 20:52:17 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_alive(t_philo	*philo)
{
	pthread_mutex_lock(&philo -> global -> death_lock);
	if (philo -> global -> died)
	{
		pthread_mutex_unlock(&philo -> global -> death_lock);
		return(0);
	}
	pthread_mutex_unlock(&philo -> global -> death_lock);
	return (1);
}


void	*action(void *data)
{
	t_philo	*philo;

	philo = data;
	while (philos_alive(philo))
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
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo -> eating);
	usleep(philo -> time_to_eat);
	philo -> time_last_eaten = now();
	philo -> num_eaten++;
	pthread_mutex_unlock(&philo -> eating);
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
