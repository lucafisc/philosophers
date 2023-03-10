
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct s_data	t_data;

typedef enum s_bool
{
	false,
	true
} t_bool;

typedef struct s_philo
{
	int index;
	u_int64_t last_meal;
	t_data *data;
	int left_fork;
	int right_fork;
} t_philo;

typedef struct s_data
{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_philosophers;
	int number_of_meals;
	u_int64_t start;
	t_philo **philosophers;
	pthread_t *threads;
	pthread_mutex_t	mutex;
	pthread_mutex_t *forks;
} t_data;


t_bool		is_valid_input(int argc, char **argv);
t_data		init_data(int argc, char *argv[]);
int			init_threads(t_data *data);
void		*routine();
int			join_threads(t_data *data);
void		destroy_philo(t_data *data);
u_int64_t	get_time(void);
u_int64_t	get_time_elapsed(u_int64_t start);


// utils
t_bool	ft_is_space(char x);
t_bool	ft_is_sign(char x);
t_bool	ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif