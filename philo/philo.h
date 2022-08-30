/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:06:54 by algaspar          #+#    #+#             */
/*   Updated: 2022/08/30 17:42:54 by algaspar         ###   ########.fr       */
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
# include <stdatomic.h>
# include <stdbool.h>

typedef struct s_instr
{
	int				philos;
	int				t_tdie;
	int				t_teat;
	int				t_tsleep;
	int				it;
	int				philos_finished;
	atomic_bool		active;
	u_int64_t		start_time;
	pthread_mutex_t	print;
}	t_instr;

typedef struct s_philo
{
	pthread_t				thread;
	int						index;
	atomic_uint_fast64_t	last_meal;
	int						times_eaten;
	pthread_mutex_t			fork;
	struct s_philo			*nextphilo;
	t_instr					*instr;
}	t_philo;

uint64_t	get_time(void);
void		my_sleep(uint64_t time);
void		*philo_main(void *arg);
void		print_time(t_philo *philo, const char *message);
int			init_instructions(int argc, char **argv, t_instr *instr);
int			init_mutex(t_philo *philo, t_instr *instr);
void		init_philos(t_philo *philo, t_instr *instr);

#endif