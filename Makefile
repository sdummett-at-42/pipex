# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 22:23:23 by sdummett          #+#    #+#              #
#    Updated: 2021/08/05 14:34:18 by sdummett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ************************************ #
#                                      #
#              VARIABLES               #
#                                      #
# ************************************ #

CC		= clang
CFLAGS	= -Wall -Werror -Wextra
NAME	= pipex
SRC		= pipex.c \
			utils/ft_split.c \
			utils/ft_calloc.c \
			utils/ft_bzero.c \
			utils/ft_strnstr.c \
			utils/ft_strjoin.c \
			rm_n_first_char.c \
			get_paths.c
INC		= -Iincludes
OBJ		= $(SRC:.c=.o)

# ************************************ #
#                                      #
#                RULES                 #
#                                      #
# ************************************ #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(INC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all