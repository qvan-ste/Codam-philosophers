/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 19:36:40 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 20:13:56 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_global *global, int l_fork, int r_fork)
{
	if (l_fork < r_fork)
	{
		pthread_mutex_lock(&global -> forks[l_fork]);
		pthread_mutex_lock(&global -> forks[r_fork]);
	}
	else
	{
		pthread_mutex_lock(&global -> forks[r_fork]);
		pthread_mutex_lock(&global -> forks[l_fork]);
	}
}

void	put_forks(t_global *global, int l_fork, int r_fork)
{
	if (l_fork < r_fork)
	{
		pthread_mutex_unlock(&global -> forks[l_fork]);
		pthread_mutex_unlock(&global -> forks[r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&global -> forks[r_fork]);
		pthread_mutex_unlock(&global -> forks[l_fork]);
	}
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
	take_forks(philo -> global, l_fork, r_fork);
	pthread_mutex_lock(&philo -> eating);
	print_action(global, id, "is eating");
	philo -> time_last_eaten = get_time();
	philo_sleep(global -> time_to_eat);
	philo -> num_eaten++;
	put_forks(philo -> global, l_fork, r_fork);
	pthread_mutex_unlock(&philo -> eating);
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
