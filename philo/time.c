/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:05:07 by algaspar          #+#    #+#             */
/*   Updated: 2022/09/08 18:03:52 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_sleep(uint64_t time)
{
	uint64_t	i;

	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break ;
		usleep(100);
	}
}

int	ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	print_time(t_philo *philo, const char *message)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->instr->print);
	time = get_time() - philo->instr->start_time;
	if (philo->instr->active || !ft_strcmp(message, "died"))
		printf("%llu %d %s\n", time, philo->index + 1, message);
	pthread_mutex_unlock(&philo->instr->print);
}
