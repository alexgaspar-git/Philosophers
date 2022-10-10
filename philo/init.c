/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:42:18 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/30 19:04:55 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo, t_instr *instr)
{
	int	i;

	i = instr->philos - 1;
	philo[i].nextphilo = &philo[0];
	while (i >= 0)
	{
		philo[i].index = i;
		philo[i].instr = instr;
		philo[i].last_meal = get_time();
		philo[i].times_eaten = 0;
		if (i < instr->philos - 1)
			philo[i].nextphilo = &philo[i + 1];
		i--;
	}
}

int	init_mutex(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->philos)
	{
		if (pthread_mutex_init(&philo[i].fork, NULL) != 0)
		{
			free(philo);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&instr->print, NULL) != 0)
	{
		free(philo);
		return (0);
	}
	init_philos(philo, instr);
	return (1);
}
