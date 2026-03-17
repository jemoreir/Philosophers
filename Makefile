# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 17:01:37 by jemoreir          #+#    #+#              #
#    Updated: 2025/12/03 17:01:37 by jemoreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -pthread

SRC = src/main.c src/init.c src/monitor.c src/philo_actions.c src/utils.c \
		src/utils_extra.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
