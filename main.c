#include "philo.h"

/*void	print_table(t_fork *head)
{
	t_philo	*philo;

	philo = head->right;
	while (philo)
	{
		printf("philo n°%d\n", philo->name);
		if (!philo->right->left)
			philo = NULL;
		else
			philo = philo->right->right;
	}
}*/

static int	set_up(t_info *rules, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("please give a correct number of arguments :\n");
		printf("1 : number of philosophers\n2 : time to die\n");
		printf("3 : time to eat\n4 : time to sleep\n");
		printf("5 (optional): number of meals every philosopher must eat\n");
		return (-1);
	}
	if (!check_nums(argv))
		return (-1);
	rules->dead = 0;
	rules->num = (int)convert(argv[1]);
	rules->ttd = convert(argv[2]);
	rules->mm = -1;
	if (argv[5])
		rules->mm = (int)convert(argv[5]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fork	*head;
	t_info	rules;
	pthread_t	watch;
	
	if (set_up(&rules, argv, argc) == -1)
		return (0);
	watch = 0;
	head = make_fork(NULL, rules.num, &rules);
	if (!head)
	{
		if (!rules.num)
			printf("no philosophers at this table\n");
		return (0);
	}
	set_table(head, rules.ttd, convert(argv[3]), convert(argv[4]));
	if (start_threads(head, &watch) == -1 || end_threads(head, &watch) == -1)
		printf("error somewhere\n");
	free_table(head);
	return (0);
}
