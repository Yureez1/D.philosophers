NAME = philo
CC = cc
CFLAGS = -Werror -Wall -Wextra -g3
HEADER = philosophers.h

SRCS = parsing.c philo_routine.c philo_mouv.c utils.c error.c init.c threads.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJS)
		@echo "\033[0;32mCompiling philo...\033[0m"
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[0;32mEverything Compiled\033[0m"

clean:
	@echo "\033[0;32mCleaning Objects files...\033[0m"
	@rm -f @$(OBJS)
		@echo "\033[0;32mObjects files cleaned\033[0m"

fclean: clean
	@echo "\033[0;32mFull cleaning...\033[0m"
	@rm -f $(NAME) $(OBJS)
		@echo "\033[0;32mEverything cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re