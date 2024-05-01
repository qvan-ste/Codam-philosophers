/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 15:21:54 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/05/01 19:41:04 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Time error\n", 11);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(t_philo *philo, char *message)
{
	struct timeval	time;
	long long		time_stamp;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Time error\n", 11);
	time_stamp = (time.tv_sec * 1000 + time.tv_usec / 1000)
		- philo -> start_time;
	printf("%lli %i %s\n", time_stamp, philo -> id, message);
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

void	check_input(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Incorrect number of arguments\n", 30);
		exit (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		write(2, "Incorrect number of philosophers\n", 33);
		exit (1);
	}
	if (ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0 || ft_atoi(argv[2]) < 1)
	{
		write (2, "Time input is invalid\n", 22);
		exit (1);
	}
	if (argv[5] && ft_atoi(argv[5]) < 0)
	{
		write(2, "Times to eat is invalid\n", 24);
		exit (1);
	}
}
