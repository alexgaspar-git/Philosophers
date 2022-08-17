/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:04:53 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/17 19:23:36 by algaspar         ###   ########.fr       */
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
			return (0);
		i++;
	}
	if (pthread_mutex_init(&instr->print, NULL) != 0)
		return (0);
	return (1);
}

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

void	check_death(t_philo *philo, t_instr *instr)
{
	int	i;

	while (instr->active)
	{
		i = 0;
		while (i < instr->philos)
		{
			if (instr->philos_finished == instr->philos)
			{
				instr->active = 0;
				break ;
			}
			if (get_time() > (philo + i)->last_meal + instr->t_tdie)
			{
				instr->active = 0;
				print_time(philo + i, "died");
				break ;
			}
		}
	}
}

int	start_philo(t_instr *instr)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * instr->philos);
	if (!philo)
		return (0);
	if (!init_mutex(philo, instr))
		return (0);
	init_philos(philo, instr);
	i = 0;
	while (i < instr->philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_main, philo + i) != 0)
			return (0);
		i++;
	}
	check_death(philo, instr);
	i = 0;
	while (i < instr->philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_instr	instr;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments\n", 28));
	if (!init_instructions(argc, argv, &instr))
		return (write(2, "Invalid argument data\n", 22));
	if (!start_philo(&instr))
		return (write(2, "Failed to start Philosophers\n", 29));
	return (0);
}