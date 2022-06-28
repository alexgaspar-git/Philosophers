/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:22:50 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/28 19:59:38 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(u_int64_t start_time)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000) - start_time);
}

void	my_sleep(uint64_t time)
{
	uint64_t	i;

	i = get_time(0);
	while (1)
	{
		if (get_time(0) - i >= time)
			break ;
		usleep(50);
	}
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
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

int	check_arg(char *arg)
{
	int	i = 0;
	
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (ft_atoi(arg) < 0 || ft_atoi(arg) > 2147483647)
		return (0);
	return (1);
}