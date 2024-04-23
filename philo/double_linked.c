/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_linked.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:37:18 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/04/23 19:23:06 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_listdoub	*ft_lstdoubnew(t_philo *philo)
{
	t_listdoub	*new;

	new = malloc(sizeof(t_listdoub));
	if (!new)
		return (NULL);
	new -> philo = philo;
	new -> prev = NULL;
	new -> next = NULL;
	return (new);
}

t_listdoub	*ft_lstdoublast(t_listdoub *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstdoubadd_back(t_listdoub **lst, t_listdoub *new)
{
	t_listdoub	*last;

	last = ft_lstdoublast(*lst);
	last -> next = new;
	new -> prev = last;
}
