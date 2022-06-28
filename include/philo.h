/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:21:36 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/28 19:59:25 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_instr
{
	int			numphilo;
	int			t_td;
	int			t_te;
	int			t_ts;
	int			iterations;
	u_int64_t	start_time;
}	t_instr;

typedef struct s_philo
{
	pthread_t	thread;
	int	index;
	pthread_mutex_t fork;
	struct s_philo *nextphilo;
	t_instr	*instr;
}	t_philo;

long		ft_atoi(const char *str);
uint64_t	get_time(u_int64_t start_time);
void		my_sleep(uint64_t time);
int			check_arg(char *arg);

#endif