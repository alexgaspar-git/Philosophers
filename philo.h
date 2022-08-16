/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:06:54 by algaspar          #+#    #+#             */
/*   Updated: 2022/06/29 22:26:57 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_instr
{
	int				philos;
	int				t_tdie;
	int				t_teat;
	int				t_tsleep;
	int				iterations;
	int				philos_finished;
	int				active;
	u_int64_t		start_time;
	pthread_mutex_t print;
}	t_instr;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	uint64_t		last_meal;
	int				times_eaten;
	pthread_mutex_t fork;
	struct s_philo	*nextphilo;
	t_instr			*instr;
}	t_philo;

uint64_t	get_time(void);
void		my_sleep(uint64_t time);
void		print_time(t_philo *philo, const char *message);
int			init_instructions(int argc, char **argv, t_instr *instr);

#endif