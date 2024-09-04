/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 19:36:40 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 15:27:09 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_global *global, int id, int l_fork, int r_fork)
{
	int	first;
	int	second;

	if (l_fork < r_fork)
	{
		first = l_fork;
		second = r_fork;
	}
	else
	{
		first = r_fork;
		second = l_fork;
	}
	pthread_mutex_lock(&global -> forks[first]);
	pthread_mutex_lock(&global -> forks[second]);
}

void	put_forks(t_global *global, int id, int l_fork, int r_fork)
{
	int	first;
	int	second;

	if (l_fork < r_fork)
	{
		first = l_fork;
		second = r_fork;
	}
	else
	{
		first = r_fork;
		second = l_fork;
	}
	pthread_mutex_unlock(&global -> forks[first]);
	pthread_mutex_unlock(&global -> forks[second]);
}

void	eating(t_philo *philo)
{
	t_global	*global;
	int			id;
	int			l_fork;
	int			r_fork;

	global = philo -> global;
	id = philo -> id;
	l_fork = philo -> l_fork;
	r_fork = philo -> r_fork;
	take_forks(global, id, l_fork, r_fork);
	pthread_mutex_lock(&philo -> eating);
	print_action(global, id, "is eating");
	philo_sleep(global -> time_to_eat);
	philo -> time_last_eaten = now();
	philo -> num_eaten++;
	pthread_mutex_unlock(&philo -> eating);
	put_forks(global, id, l_fork, r_fork);
}

void	*start_simulation(void *data)
{
	t_philo	*philo;

	philo = data;
	sync_start(philo);
	while (!end_of_sim(philo -> global))
	{
		eating(philo);
		print_action(philo -> global, philo -> id, "is sleeping");
		philo_sleep(philo -> global -> time_to_sleep);
		print_action(philo -> global, philo -> id, "is thinking");
	}
	return (NULL);
}
