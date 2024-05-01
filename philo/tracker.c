/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tracker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 13:14:17 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 19:39:34 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eaten(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (philo -> next != head)
	{
		if (philo -> num_eaten < philo -> num_should_eat)
			return (0);
	}
	return (1);
}

void	*track_philosophers(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
	{
		if (!philo -> is_eating
			&& now() - philo -> time_last_eaten >= philo -> time_to_die)
		{
			print_action(philo, "died");
			break ;
		}
		philo = philo -> next;
	}
	return (NULL);
}
