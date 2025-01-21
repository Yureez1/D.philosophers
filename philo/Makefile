NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
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

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR = obj

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[34mPHILO COMPILED\033[0m"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[34mCLEANING OBJ DIRECTORY\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[34mCLEANING PHILO\033[0m"

re: fclean all

.PHONY: all clean fclean re