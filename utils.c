#include "philo.h"

useconds_t	getnow(useconds_t before)
{
	struct timeval	now;
	useconds_t	time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000000 + now.tv_usec;
	time = (time / 1000) - before;
	return (time);
}

void	free_table(t_fork *head)
{
	t_philo *philo;

	philo = head->right;
	pthread_mutex_destroy(&(philo->rules->lock));
	pthread_mutex_destroy(&(philo->rules->print));
	while (philo)
	{
		pthread_mutex_destroy(&(philo->right->lock));
		if (philo->right->left && philo->right->right)
		{
			philo = philo->right->right;
			free(philo->left->left);
			free(philo->left);
		}
		else
		{
			free(philo->right);
			free(philo);
			philo = NULL;
		}
	}
}

static void	printer(useconds_t time, t_philo *philo, int action)
{
	pthread_mutex_lock(&(philo->rules->print));
	printf("%u %d ", /*((*/time/*) / 100) * 100*/, philo->name);
	if (!action)
		printf("has died\n");
	else if (action == 1)
		printf("is eating\n");
	else if (action == 3)
		printf("is thinking\n");
	else if (action == 2)
		printf("is sleeping\n");
	else if (action == 4)
		printf("has grabbed left fork : %c\n", philo->left->num);
	else if (action == 5)
		printf("has grabbed right fork : %c\n", philo->right->num);
	pthread_mutex_unlock(&(philo->rules->print));
}

void	printing_press(t_philo *philo, int action)
{
	useconds_t	before;

	if (!philo)
		return ;
	pthread_mutex_lock(&(philo->rules->lock));
	before = philo->rules->before;
	if (action && philo->rules->dead == -1)
	{
		pthread_mutex_unlock(&(philo->rules->lock));
		return ;
	}
	pthread_mutex_unlock(&(philo->rules->lock));
	printer(getnow(0) - before, philo, action);
}

int	check_dead(t_philo *philo)
{
	t_info	*rules;

	if (philo->left == philo->right)
	{
		solo_philo(philo);
		return (1);
	}
	rules = philo->rules;
	pthread_mutex_lock(&(rules->lock));
	if (rules->dead == -1)
	{
		pthread_mutex_unlock(&(rules->lock));
		return (1);
	}
	pthread_mutex_unlock(&(rules->lock));
	return (0);
}

