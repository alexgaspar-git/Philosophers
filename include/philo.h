/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:21:36 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/27 15:43:03 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			index;
	int			fork;
}	t_philo;

typedef struct s_instr
{
	t_philo	*philo;
	int	numphilo;
	int t_td;
	int	t_te;
	int	t_ts;
	int	iterations;;
}	t_instr;

long		ft_atoi(const char *str);
uint64_t	get_time(void);
void		my_sleep(uint64_t time);
int			check_arg(char *arg);

#endif