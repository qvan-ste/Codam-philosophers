/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:28 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/04/23 20:03:46 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	long long 	start_time;
	int			num_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_should_eat;
	long long	time_last_eaten;
	int			time_till_death;
	int			time_sleeping;
	int			is_dead;

} t_philo;

typedef struct s_listdoub
{
	t_philo				*philo;
	struct s_listdoub	*prev;
	struct s_listdoub	*next;
}	t_listdoub;


int			ft_atoi(const char *str);
t_listdoub	*ft_lstdoubnew(t_philo *philo);
t_listdoub	*ft_lstdoublast(t_listdoub *lst);
void		ft_lstdoubadd_back(t_listdoub **lst, t_listdoub *new);
t_listdoub	*create_philosophers(int argc, char *argv[]);
t_philo 	*init_philosopher(int argc, char*argv[], int id);
void 		*decider(void *data);
void 		eating(t_philo *philo);
void 		sleeping(t_philo *philo);
void		thinking(t_philo *philo);