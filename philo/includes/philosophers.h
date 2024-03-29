/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:07:31 by lde-ross          #+#    #+#             */
/*   Updated: 2023/03/14 20:39:28 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_data	t_data;

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	int			index;
	u_int64_t	last_meal;
	t_data		*data;
	int			first_fork;
	int			second_fork;
	int			times_ate;
}	t_philo;

typedef struct s_data
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_philosophers;
	int				number_of_meals;
	t_bool			terminate;
	u_int64_t		start;
	t_philo			**philosophers;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	times_ate_mutex;
	pthread_mutex_t	terminate_mutex;
	pthread_mutex_t	*forks;
}		t_data;

t_bool		is_valid_input(int argc, char **argv);
t_data		*init_data(int argc, char *argv[]);
int			init_threads(t_data *data);
void		*routine(void *arg);
int			join_threads(t_data *data);
void		destroy_philo(t_data *data);
u_int64_t	get_time(void);
u_int64_t	get_time_elapsed(u_int64_t start);
void		*monitor(void *arg);
void		*one_philosopher(t_philo *philo);
t_bool		should_terminate(t_data *data);
void		toggle_terminate(t_data *data);
t_bool		is_dead(t_philo *philo);
void		print_message(int message, t_philo *philo);
int			print_error(void);
t_bool		is_full(t_philo *philo);
t_bool		ft_is_space(char x);
t_bool		ft_is_sign(char x);
t_bool		ft_isdigit(int c);
int			ft_atoi(const char *str);

#endif