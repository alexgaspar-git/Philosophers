/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:47:36 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/26 17:46:28 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	numphilo;
	int t_td;
	int	t_te;
	int	t_ts;
	int	iterations;
}	t_philo;

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	my_sleep(uint64_t time)
{
	uint64_t	i;

	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break ;
		usleep(50);
	}
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
	long	i;
	long	nbr;
	int		isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		isneg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	if (nbr < 0 && isneg == 1)
		return (-1);
	else if (nbr < 0 && isneg == 0)
		return (-1);
	if (isneg == 1)
		return (-nbr);
	return (nbr);
}

int	parsing(int argc, char **argv, t_philo *philo)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	philo->numphilo = ft_atoi(argv[1]);
	philo->t_td = ft_atoi(argv[2]);
	philo->t_te = ft_atoi(argv[3]);
	philo->t_ts = ft_atoi(argv[4]);
	if (argc == 6)
		philo->iterations = ft_atoi(argv[5]);
	else
		philo->iterations = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo philo;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	if (!parsing(argc, argv, &philo))
	{
		write(2, "Invalid argument data\n", 22);
		return (2);
	}
	
	return (0);
}