/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 17:19:24 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/06/03 19:20:51 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

t_list	*ft_lstlast(t_list *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	last -> next = new;
}

t_list	*ft_lstnew(int id)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> id = id;
	new -> next = NULL;
	return (new);
}

int add_to_queue(t_philo *philo, int id)
{
	t_list	*new;
	
	new = ft_lstnew(philo -> id);
	philo -> global -> queue[id] = new;
	if (!new)
		return (-1);
	pthread_mutex_lock(&philo -> global -> queue_lock);
	if (philo -> global -> queue[id])
		ft_lstadd_back(&philo -> global -> queue[id], new);
	else
		philo -> global -> queue[id] = new;
	pthread_mutex_unlock(&philo -> global -> queue_lock);
	return (0);
}

int first_in_queue(t_philo *philo, int id)
{
	t_list	*tmp;
	
	pthread_mutex_lock(&philo -> global -> queue_lock);
	if (philo -> id == philo -> global -> queue[id] -> id)
	{
		tmp = philo -> global -> queue[id];
		philo -> global -> queue[id] = philo -> global -> queue[id] -> next;
		free (tmp);
		pthread_mutex_unlock(&philo -> global -> queue_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo -> global -> queue_lock);
	return (0);
}


