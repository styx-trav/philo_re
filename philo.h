#ifndef FIRST_H
# define FIRST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_info
{
	int dead;
	useconds_t before;
	pthread_mutex_t lock;
	pthread_mutex_t print;
	pthread_mutex_t eat;
	useconds_t ttd;
	int num;
	int mm;
}                 t_info;

typedef struct	s_philo
{
	struct s_fork *left;
	struct s_fork *right;
	pthread_t num;
	int name;
	int meals;
	useconds_t last_meal;
	useconds_t ttd;
	useconds_t tte;
	useconds_t tts;
	t_info *rules;
}		t_philo;

typedef struct	s_fork
{
	t_philo *left;
	t_philo *right;
	char num;
	pthread_mutex_t lock;
}		t_fork;

//from watchdog.c
void	*watchdog(void *philos);

//from utils.c
void	free_table(t_fork *head);
useconds_t	getnow(useconds_t before);
void	printing_press(t_philo *philo, int action);
int	check_dead(t_philo *philo);

//from philos.c
void	*philo_does(void *param);
void	solo_philo(t_philo *philo);

//from init.c
void	set_table(t_fork *head, int ttd, int tte, int tts);
t_philo	*make_philo(t_fork *left, int num, t_info *rules);
t_fork	*make_fork(t_philo *left, int num, t_info *rules);

//from threading.c
int	start_threads(t_fork *head, pthread_t *watch);
int	end_threads(t_fork *head, pthread_t *watch);

//from parsing.c
int	check_nums(char **argv);
useconds_t	convert(char *arg);

#endif
