/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:21:54 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/29 14:34:50 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(t_philo *philo, char *message)
{
	long long		time_stamp;
	
	time_stamp = now() - philo -> start_time;
	if (time_stamp == -1)
		return ;
	pthread_mutex_lock(&philo -> global -> print_lock);
	if (!end_of_sim(philo))
		printf("%lli %i %s\n", time_stamp, philo -> id, message);
	pthread_mutex_unlock(&philo -> global -> print_lock);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}


int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while(argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
				return (write(2, "Input contains invalid characters\n", 34));
		}
		j = 0;
		i++;
	}
	if (argc != 5 && argc != 6)
		return(write(2, "Incorrect number of arguments\n", 30));
	if (ft_atoi(argv[1]) < 1)
		return (write(2, "Incorrect number of philosophers\n", 33));
	if (ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0 || ft_atoi(argv[2]) < 1)
		return (write (2, "Time input is invalid\n", 22));
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (write(2, "Times to eat is invalid\n", 24));
	return (0);
}
