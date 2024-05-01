/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 13:14:17 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 20:53:52 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (1)
	{
		pthread_mutex_lock(&philo -> eating);
		if (philo -> num_eaten < philo -> num_should_eat)
		{
			pthread_mutex_unlock(&philo -> eating);
			return (0);	
		}
		pthread_mutex_unlock(&philo -> eating);
		philo = philo -> next;
		if (philo == head)
			break ;
	}
	return (1);
}

int died(t_philo *philo)
{
	pthread_mutex_lock(&philo -> eating);
	if (now() - philo -> time_last_eaten >= philo -> time_to_die)
	{
		pthread_mutex_lock(&philo -> global -> death_lock);
		philo -> global -> died = 1;
		pthread_mutex_unlock(&philo -> global -> death_lock);
		pthread_mutex_unlock(&philo -> eating);
		return (1);	
	}
	pthread_mutex_unlock(&philo -> eating);
	return (0);
}

void	*track_philosophers(void *data)
{
	t_philo		*philo;

	philo = data;
	all_eaten(philo);
	while (1)
	{
		if (died(philo))
		{
			print_action(philo, "died");
			break ;
		}
		// if (philo -> num_should_eat > 0 && philo -> num_eaten >= philo -> num_should_eat)
		// {
		// 	if (all_eaten(philo))
		// 	{
		// 		printf ("All philosophers eaten\n");
		// 		break ;
		// 	}
		// }
		philo = philo -> next;
	}
	return (NULL);
}
