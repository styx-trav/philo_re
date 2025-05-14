#include "philo.h"

t_fork	*make_fork(t_philo *left, int num, t_info *rules)
{
	t_fork	*fork;

	if (!num)
		return (NULL);
	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->right = NULL;
	fork->left = left;
	if (pthread_mutex_init(&(fork->lock), NULL) != 0)
	{
		perror("mutex init :");
		free(fork);
		return (NULL);
	}
	fork->right = make_philo(fork, num, rules);
	if (!fork->right)
	{
		pthread_mutex_destroy(&(fork->lock));
		free(fork);
		return (NULL);
	}
	return (fork);
}

t_philo	*make_philo(t_fork *left, int num, t_info *rules)
{
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->rules = rules;
	philo->name = 0;
	philo->num = 0;
	philo->last_meal = 0;
	philo->meals = 0;
	philo->left = left;
	philo->right = NULL;
	philo->right = make_fork(philo, num - 1, rules);
	if (!philo->right && num - 1)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	set_table(t_fork *head, int ttd, int tte, int tts)
{
	t_fork	*tmp;
	int	i;
	t_philo	*philo;

	tmp = head;
	i = 1;
	while (tmp)
	{
		tmp->num = i - 1 + 'a';
		philo = tmp->right;
		philo->name = i;
		philo->ttd = ttd;
		philo->tte = tte;
		philo->tts = tts;
		tmp = philo->right;
		i++;
	}
	philo->right = head;
}
