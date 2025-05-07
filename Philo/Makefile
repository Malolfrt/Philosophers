# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 17:17:50 by mlefort           #+#    #+#              #
#    Updated: 2024/03/28 12:29:11 by mlefort          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= clang
CFLAGS	= -Wall -Werror -Wextra

SRC_PATH	= src/
OBJ_PATH	= src/obj/

SRC_FILES	= 	main.c \
				utils.c \
				parsing.c \
				dinning.c \
				init_value.c \
				dinning_utils.c


OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_FILES))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf *.o $(OBJ_PATH)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
