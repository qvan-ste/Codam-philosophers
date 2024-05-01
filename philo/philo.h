/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:28 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 19:29:11 by qvan-ste      ########   odam.nl         */
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
	int				id;
	pthread_t		thread_id;
	long long 		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_eating;
	int				num_eaten;
	int				num_should_eat;
	long long		time_last_eaten;
	pthread_mutex_t	fork_in_use;
	struct s_philo	*next;
} t_philo;

int			ft_atoi(const char *str);
t_philo		*create_philosophers(char*argv[]);
void 		*action(void *data);
void		take_forks(t_philo *philo);
void 		eating(t_philo *philo);
void 		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		check_input(int argc, char *argv[]);
void 		print_action(t_philo *philo, char *message);
long long 	now(void);
void 		*track_philosophers(void *data);
int 		check_all_eaten(t_philo *philo);
