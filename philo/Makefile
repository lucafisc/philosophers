FILES = ./src/main.c ./src/input_check.c ./src/init.c ./src/utils.c ./src/routine.c ./src/destroy.c ./src/time.c
OBJECTS = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(B_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all