NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c philo.c init.c error.c monitoring.c philo_utils.c monitoring_utils.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "\033[32mCompiling $(NAME)\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32m$(NAME) compiled\033[0m"

clean:
	@echo "\033[32mCleaning object files\033[0m"
	@rm -rf $(OBJ_DIR)
	@echo "\033[32mObject files cleaned\033[0m"

fclean: clean
	@echo "\033[32mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)
	@echo "\033[32m$(NAME) cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re
