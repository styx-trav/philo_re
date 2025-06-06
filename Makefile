CC=cc
FLAGS=-Wall -Werror -Wextra
SRC=main.c\
parsing.c\
init.c\
threading.c\
philos.c\
utils.c\
watchdog.c
NAME=philo

all: $(NAME)

$(NAME): $(SRC) philo.h
	$(CC) $(FLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

run: $(NAME)
	./$(NAME) 4 600 200 200 2

.PHONY: clean all re fclean
