#include "philo.h"

void	solo_philo(t_philo *philo)
{
	useconds_t	time;

	pthread_mutex_lock(&(philo->left->lock));
	printing_press(philo, 4);
	time = philo->rules->before;
	while (getnow(0) < time + philo->ttd)
		usleep(10);
	printing_press(philo, 0);
	pthread_mutex_unlock(&(philo->left->lock));
}

static void	grab_forks(t_philo *philo)
{
	if (!(philo->name % 2))
	{
		usleep(2);
		pthread_mutex_lock(&(philo->right->lock));
		printing_press(philo, 5);
		pthread_mutex_lock(&(philo->left->lock));
		printing_press(philo, 4);
	}
	else
	{
		pthread_mutex_lock(&(philo->left->lock));
		printing_press(philo, 4);
		pthread_mutex_lock(&(philo->right->lock));
		printing_press(philo, 5);
	}
	pthread_mutex_lock(&(philo->rules->eat));
	philo->last_meal = getnow(0);
	philo->meals++;
	pthread_mutex_unlock(&(philo->rules->eat));
}

static void	forks_down(t_philo *philo)
{
	if (!(philo->name % 2))
	{
		pthread_mutex_unlock(&(philo->right->lock));
		pthread_mutex_unlock(&(philo->left->lock));
	}
	else
	{
		pthread_mutex_unlock(&(philo->left->lock));
		pthread_mutex_unlock(&(philo->right->lock));
	}
}

void	*philo_does(void *data)
{
	t_philo	*philo;
	useconds_t time;

	philo = (t_philo *)data;
	//pthread_mutex_lock(&(philo->rules->lock));
	pthread_mutex_lock(&(philo->rules->eat));
	philo->last_meal = philo->rules->before;
	//pthread_mutex_unlock(&(philo->rules->lock));
	pthread_mutex_unlock(&(philo->rules->eat));
	while (!check_dead(philo))
	{
		grab_forks(philo);
		time = getnow(0);
		printing_press(philo, 1);
		while (getnow(0) < time + philo->tte)
			usleep(10);
		time = getnow(0);
		printing_press(philo, 2);
		forks_down(philo);
		while (getnow(0) < time + philo->tts)
			usleep(10);
		printing_press(philo, 3);
		usleep(10);
	}
	return (NULL);
}
