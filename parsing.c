#include "philo.h"

static int	is_num(char a)
{
	if (a <= '9' && a >= '0')
		return (1);
	return (0);
}

static int	check_num(char *arg, int argv)
{
	int	ct;
	int	i;

	ct = 0;
	i = 0;
	while (arg[i] && is_num(arg[i]))
	{
		ct = ct * 10 + arg[i] - '0';
		if (ct < 0)
			return (0);
		i++;
	}
	if ((argv != 1 || !is_num(arg[0])) && ct == 0)
		return (0);
	if (arg[i])
		printf("warning: argument n°%d has non numerical characters (ignored)\n", argv);
	return (1);
}

int	check_nums(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_num(argv[i], i))
		{
			printf("argument n°%d : invalid input\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

useconds_t	convert(char *arg)
{
	useconds_t	num;
	int	i;

	i = 0;
	num = 0;
	while (arg[i] && is_num(arg[i]))
	{
		num = num * 10 + arg[i] - '0';
		i++;
	}
	return (num);
}
