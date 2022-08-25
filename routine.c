/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:22:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/25 19:47:44 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_time(philo, "has taken a fork");
	if (philo->instr->philos < 2)
	{
		my_sleep(philo->instr->t_tdie + 100);
		return (true);
	}
	pthread_mutex_lock(&philo->nextphilo->fork);
	print_time(philo, "has taken a fork");
	print_time(philo, "is eating");
	philo->last_meal = get_time();
	my_sleep(philo->instr->t_teat);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->nextphilo->fork);
	philo->instr->philos_finished += philo->times_eaten == philo->instr->it;
	if (philo->instr->active == 0)
		return (true);
	print_time(philo, "is sleeping");
	my_sleep(philo->instr->t_tsleep);
	print_time(philo, "is thinking");
	return (!philo->instr->active);
}

void	*philo_main(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 1)
		my_sleep(50);
	while (1)
		if (philo_routine(philo))
			break ;
	return (0);
}
