#include "philo.h"

static void	detach(t_philo *head, t_philo *end, int unlock)
{
	if (unlock)
		pthread_mutex_unlock(&(head->rules->lock));
	while (head)
	{
		pthread_detach(head->num);
		if (!head->right->left || head->right->right == end)
			head = NULL;
		else
			head = head->right->right;
	}
}

static int	mutex_watch(t_philo *philo, pthread_t *watch)
{
	if (pthread_mutex_init(&(philo->rules->lock), NULL) != 0
		|| pthread_mutex_init(&(philo->rules->print), NULL) != 0
		|| pthread_mutex_init(&(philo->rules->eat), NULL) != 0)
	{
		perror("mutex inits");
		return (-1);
	}
	if (philo->right != philo->left && pthread_create(watch, NULL, &watchdog, philo))
	{
		perror("starting watchdog");
		return (-1);
	}
	return (0);
}

int	start_threads(t_fork *head, pthread_t *watch)
{
	t_philo	*philo;

	philo = head->right;
	philo->rules->before = 0;
	if (mutex_watch(philo, watch) == -1)
		return (-1);
	pthread_mutex_lock(&(philo->rules->eat));
	while (philo)
	{
		if (pthread_create(&(philo->num), NULL, &philo_does, philo))
		{
			perror("starting threads");
			detach(head->right, philo, 1);
			return (-1);
		}
		if (!philo->right->left)
			philo = NULL;
		else
			philo = philo->right->right;
	}
	head->right->rules->before = getnow(0);
	pthread_mutex_unlock(&(head->right->rules->eat));
	return (0);
}

int	end_threads(t_fork *head, pthread_t *watch)
{
	t_philo	*philo;
	void	*interest;

	philo = head->right;
	while (philo)
	{
		if (pthread_join(philo->num, &interest))
		{
			perror("ending threads");
			detach(philo, NULL, 0);
			return (-1);
		}
		if (!philo->right->left)
			philo = NULL;
		else
			philo = philo->right->right;
	}
	if (head != head->right->right && pthread_join(*watch, &interest))
	{
		perror("ending threads");
		return (-1);
	}
	return (0);
}
