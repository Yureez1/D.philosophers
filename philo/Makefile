NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
HEADER = philosophers.h

SRC = main.c \
	utils.c \
	init_utils.c \
	init_philo.c \
	monitor.c \
	death.c \
	simulation.c \
	cleanup.c \
	philo_actions.c \
	philo_checks.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re