/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:05:07 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/29 22:06:21 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(u_int64_t start_time)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time);
}

void	my_sleep(uint64_t time)
{
	uint64_t	i;

	i = get_time(0);
	while (1)
	{
		if (get_time(0) - i >= time)
			break ;
		usleep(100);
	}
}

void	print_time(t_philo *philo, const char *message)
{
	u_int64_t time;

	time = get_time(0) - philo->instr->start_time;
	pthread_mutex_lock(&philo->instr->print);
	if (philo->instr->active == 1)
		printf("%llu %d %s\n", time, philo->index, message);	
	pthread_mutex_unlock(&philo->instr->print);
}
