/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:47:36 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/28 20:16:15 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int argc, char **argv, t_instr *instr)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!check_arg(argv[i]))
			return (0);
		i++;
	}
	instr->numphilo = (int)ft_atoi(argv[1]);
	instr->t_td = (int)ft_atoi(argv[2]);
	instr->t_te = (int)ft_atoi(argv[3]);
	instr->t_ts = (int)ft_atoi(argv[4]);
	if (argc == 6)
		instr->iterations = (int)ft_atoi(argv[5]);
	else
		instr->iterations = 0;
	return (1);
}

void	init_philo(t_philo *philo, t_instr *instr)
{
	int	i;

	i = instr->numphilo - 1;
	while (i >= 0)
	{
		philo[i].index = i;
		philo[i].instr = instr;
		if (i < instr->numphilo - 1)
			philo[i].nextphilo = &philo[i + 1];
		i--;
	}
	philo[instr->numphilo - 1].nextphilo = &philo[0];
	instr->start_time = get_time(0);
}

void	print_time(t_philo *philo, const char *message)
{
	u_int64_t time;

	time = get_time(0) - philo->instr->start_time;
	printf("%llu %d %s\n", time, philo->index, message);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->index % 2 == 0)
		my_sleep(50);
	pthread_mutex_lock(&philo->fork);
	print_time(philo, "has taken a fork");
	pthread_mutex_lock(&philo->nextphilo->fork);
	print_time(philo, "has taken a fork");
	print_time(philo, "is eating");
	my_sleep(philo->instr->t_te);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->nextphilo->fork);
	print_time(philo, "is sleeping");
	my_sleep(philo->instr->t_ts);
	print_time(philo, "is thinking");
	return (arg);
}

void	start_philo(t_instr *instr)
{
	t_philo *philo;
	int	i;
	
	philo = malloc(sizeof(t_philo) * instr->numphilo);
	if (!philo)
		return ;
	i = 0;
	init_philo(philo, instr);
	while (i < instr->numphilo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		if (pthread_create(&philo[i].thread, NULL, (void *)philo_routine, philo + i) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < instr->numphilo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ;
		i++;
		pthread_mutex_destroy(&philo[i].fork);
	}
}

int	main(int argc, char **argv)
{
	t_instr instr;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments\n", 28));
	if (!parsing(argc, argv, &instr))
		return (write(2, "Invalid argument data\n", 22));
	start_philo(&instr);
	return (0);
}