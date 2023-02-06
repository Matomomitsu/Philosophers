# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 17:31:31 by mtomomit          #+#    #+#              #
#    Updated: 2023/02/06 09:29:53 by mtomomit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Paths
PATH_SRC = ./src/
PHILO = ./include/philosophers.a
INC_PATH = ./include/
HEADER = $(INC_PATH)philosophers.h
OBJ_DIR = ./objs/
OBJS = $(SRCS:$(PATH_SRC)%.c=$(OBJ_DIR)%.o)

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pthread #-fsanitize=thread
RM = rm -rf
INCLUDE = -I $(INC_PATH)

# Library flags
LIB_FLAGS = ar -rcs

SRCS = $(PATH_SRC)ft_atouli.c \
	   $(PATH_SRC)ft_strtod.c \
	   $(PATH_SRC)init_data.c \
	   $(PATH_SRC)philosophers.c \
	   $(PATH_SRC)utils.c \
	   $(PATH_SRC)init_data.c \
	   $(PATH_SRC)routine.c \
	   $(PATH_SRC)checker.c \
	   $(PATH_SRC)eat.c \
	   $(PATH_SRC)sleep.c \
	   $(PATH_SRC)sanitization.c

all: $(OBJ_DIR) $(PHILO) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(PATH_SRC)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(PHILO): $(OBJS)
	$(LIB_FLAGS) $(PHILO) $(OBJS)

$(NAME): $(PHILO) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(PHILO)

clean:
	$(RM) $(PHILO) $(OBJS) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
