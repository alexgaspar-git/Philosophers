/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:05:58 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/17 19:23:02 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static long	ft_atoi(const char *str)
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

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
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

static int	invalid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_instructions(int argc, char **argv, t_instr *instr)
{
	if (!invalid_args(argc, argv))
		return (0);
	instr->philos = (int)ft_atoi(argv[1]);
	instr->t_tdie = (int)ft_atoi(argv[2]);
	instr->t_teat = (int)ft_atoi(argv[3]);
	instr->t_tsleep = (int)ft_atoi(argv[4]);
	instr->active = 1;
	instr->start_time = get_time();
	instr->it = -1;
	if (argc == 6)
		instr->it = (int)ft_atoi(argv[5]);
	if (instr->it == 0 || instr->philos == 0)
		instr->active = 0;
	return (1);
}