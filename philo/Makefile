# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julien <julien@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 16:40:50 by julien            #+#    #+#              #
#    Updated: 2025/05/10 17:05:53 by julien           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = init.c main.c philo_routine.c philo_utils.c utils.c
OBJ = $(SRC:.c=.o)

LILA = \033[1;38;5;206m
GREEN = \033[32m
NC = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(LILA)Compilation philo...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Compilation reussie!$(NC)"

clean:
	@echo "$(LILA)Nettoyage...$(NC)"
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "$(GREEN)Nettoyage termine!$(NC)"

fclean: clean
	@echo "$(LILA)Nettoyage total...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Nettoyage total termine!$(NC)"

re: fclean all

.PHONY: all clean fclean re