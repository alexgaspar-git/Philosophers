/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:04:53 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/30 17:42:26 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	create_philos(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_main, philo + i) != 0)
		{
			free(philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_philos(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			free(philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	start_philo(t_instr *instr)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * instr->philos);
	if (!philo)
		return (0);
	if (!init_mutex(philo, instr))
		return (0);
	if (!create_philos(philo, instr))
		return (0);
	check_death(philo, instr);
	if (!join_philos(philo, instr))
		return (0);
	free(philo);
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
