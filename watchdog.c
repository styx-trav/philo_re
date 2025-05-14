#include "philo.h"

static void	death(t_philo *philo, int dies)
{
	if (!philo)
		return ;
	pthread_mutex_lock(&(philo->rules->lock));
	philo->rules->dead = -1;
	pthread_mutex_unlock(&(philo->rules->lock));
	if (dies)
		printing_press(philo, 0);
}

static int	is_dead(t_philo *philo, int *count, int num)
{
	pthread_mutex_lock(&(philo->rules->eat));
	if (!philo->last_meal)
		philo->last_meal = philo->rules->before;
	else if (getnow(0) >= philo->last_meal + philo->rules->ttd)
	{
		pthread_mutex_unlock(&(philo->rules->eat));
		death(philo, 1);
		return (1);
	}
	if (philo->rules->mm != -1 && philo->meals >= philo->rules->mm)
		*count = *count + 1;
	pthread_mutex_unlock(&(philo->rules->eat));
	if (*count == num)
	{
		death(philo, 0);
		return (1);
	}
	return (0);
}

void	*watchdog(void *philos)
{
	t_philo	*philo;
	int	count;

	count = 0;
	philo = (t_philo *)philos;
	pthread_mutex_lock(&(philo->rules->start));
	pthread_mutex_unlock(&(philo->rules->start));
	while (1)
	{
		philo = (t_philo *)philos;
		count = 0;
		while (philo)
		{
			if (is_dead(philo, &count, philo->rules->num))
				return (NULL);
			if (philo->right->left)
				philo = philo->right->right;
			else
				philo = NULL;
		}
	}
	return (NULL);
}
