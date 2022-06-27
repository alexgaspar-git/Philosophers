/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:47:36 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/27 16:06:05 by algaspar         ###   ########.fr       */
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

void	init_philo(t_instr *instr)
{
	
}

int	main(int argc, char **argv)
{
	t_instr instr;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments\n", 28));
	if (!parsing(argc, argv, &instr))
		return (write(2, "Invalid argument data\n", 22));
	init_philo(&instr);
	return (0);
}