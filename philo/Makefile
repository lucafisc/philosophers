FILES = ./src/main.c ./src/input_check.c ./src/init.c ./src/utils.c ./src/routine.c ./src/destroy.c ./src/time.c ./src/monitor.c ./src/print_message.c ./src/philo_utils.c
OBJECTS = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -fsanitize=thread -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(B_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all