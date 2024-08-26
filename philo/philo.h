/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:28 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/08/26 17:35:39 by qvan-ste      ########   odam.nl         */
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
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eaten;
	int				num_should_eat;
	long long		time_last_eaten;
	pthread_mutex_t	fork_in_use;
	pthread_mutex_t	eating;
	struct s_philo	*next;
	struct s_global *global;
} t_philo;


typedef struct s_global
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	ate_lock;
	pthread_mutex_t	print_lock;
	long long 		start_time;
	int				all_ate;
	int				died;
} t_global;


int			ft_atoi(const char *str);
t_philo		*create_philosophers(char*argv[]);
void		*start_simulation(void *data);
void		take_forks(t_philo *philo);
void 		eating(t_philo *philo);
void 		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
int			check_input(int argc, char *argv[]);
void 		print_action(t_philo *philo, char *message);
long long 	now(void);
void 		*track_philosophers(void *data);
int 		check_all_eaten(t_philo *philo);
int 		end_of_sim(t_philo	*philo);
void 		free_global(t_global	*global);
void 		free_philos(t_philo *philos);
void		philo_sleep(int duration);
