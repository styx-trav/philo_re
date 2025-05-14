#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	check_nums(char **argv);
useconds_t	convert(char *arg);

int main(int argc, char **argv)
{
  printf("received %d args\n", argc);
  if (!check_nums(argv))
    return (0);
  printf("arg1 %u, arg2 %u, arg3 %u, arg4 %u", convert(argv[1]), convert(argv[2]), convert(argv[3]), convert(argv[4]));
  if (argv[5])
    printf(", arg5 %u", convert(argv[5]));
  printf("\n");
  return (0);
}
