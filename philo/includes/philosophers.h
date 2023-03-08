
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

typedef enum s_bool
{
	false,
	true
} t_bool;

typedef struct s_philo
{
	int index;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_philosophers;
} t_philo;

typedef struct s_data
{
	int number_of_philosophers;
	int number_of_times_eat;
	t_philo **philosophers;
	pthread_t *threads;
} t_data;

// struct timeval
// {
// 	time_t tv_sec;
// 	suseconds_t tv_usec;
// }

t_bool
is_valid_input(int argc, char **argv);
t_data init_philo(int argc, char *argv[]);
int init_threads(t_data *data);
void *routine();
int join_threads(t_data *data);
void destroy_philo(t_data *data);
u_int64_t get_time(void);


// utils
t_bool ft_is_space(char x);
t_bool ft_is_sign(char x);
t_bool ft_isdigit(int c);
int ft_atoi(const char *str);

#endif