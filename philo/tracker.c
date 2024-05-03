/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 13:14:17 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/03 18:44:59 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	announce_end(t_philo *philo)
{
	long long		time_stamp;
	
	time_stamp = now() - philo -> start_time;
	if (time_stamp == -1)
		return ;
	if (end_of_sim(philo) == 1)
		printf("%lli %i died\n", time_stamp, philo -> id);
	else
	 	printf("%lli all philosophers have full tummies\n", time_stamp);
}

int end_of_sim(t_philo	*philo)
{
	pthread_mutex_lock(&philo -> global -> death_lock);
	if (philo -> global -> died)
	{
		pthread_mutex_unlock(&philo -> global -> death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo -> global -> death_lock);
	pthread_mutex_lock(&philo -> global -> ate_lock);
	if (philo -> global -> all_ate)
	{
		pthread_mutex_unlock(&philo -> global -> ate_lock);
		return (2);
	}
	pthread_mutex_unlock(&philo -> global -> ate_lock);
	return (0);	
}

int	all_ate(t_philo *philo)
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
	pthread_mutex_lock(&philo -> global -> ate_lock);
	philo -> global -> all_ate = 1;
	pthread_mutex_unlock(&philo -> global -> ate_lock);
	return (1);
}

int died(t_philo *philo)
{
	pthread_mutex_lock(&philo -> eating);
	if (now() - philo -> time_last_eaten >= philo -> time_to_die)
	{
		pthread_mutex_unlock(&philo -> eating);
		pthread_mutex_lock(&philo -> global -> death_lock);
		philo -> global -> died = 1;
		pthread_mutex_unlock(&philo -> global -> death_lock);
		return (1);	
	}
	pthread_mutex_unlock(&philo -> eating);
	return (0);
}

void	*track_philosophers(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
	{
		if (died(philo))
		{
			announce_end(philo);
			break ;
		}
		pthread_mutex_lock(&philo -> eating);
		if (philo -> num_should_eat > 0 && philo -> num_eaten >= philo -> num_should_eat)
		{
			pthread_mutex_unlock(&philo -> eating);
			if (all_ate(philo))
			{
				announce_end(philo);
				break ;
			}
		}
		pthread_mutex_unlock(&philo -> eating);
		philo = philo -> next;
	}
	return (NULL);
}
