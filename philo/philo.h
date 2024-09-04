/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:04:28 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/09/04 15:22:55 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_global	t_global;

typedef enum e_sim_stat
{
	INIT,
	RUNNING,
	END,
}	t_sim_stat;

typedef struct s_philo
{
	int				id;
	int				num_eaten;
	long long		time_last_eaten;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	eating;
	pthread_t		thread_id;
	t_global		*global;
}	t_philo;

typedef struct s_global
{
	unsigned int		num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_should_eat;
	long long			start_time;
	t_sim_stat			status;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		status_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}	t_global;

// Utils
void		print_action(t_global *global, int id, char *message);
long long	now(void);
bool		end_of_sim(t_global *global);
void		philo_sleep(int duration);
void		sync_start(t_philo *philo);

// Parsing
int			ft_atoi(const char *str);
int			check_input(int argc, char *argv[]);

// Init
int			init_global(t_global *global, char **argv);
int			init_mutexes(t_global *global);
int			init_philos(t_global *global);

// Routine
void		*start_simulation(void *data);
void		eating(t_philo *philo);
void		take_forks(t_global *global, int id,
				int left_philo, int right_philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

// Tracker
void		*track_philosophers(void *data);
int			check_all_eaten(t_philo *philo);
bool		all_ate(t_global *global);	
bool		philo_died(t_global *global);
