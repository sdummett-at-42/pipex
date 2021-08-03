# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stone <stone@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 22:23:23 by sdummett          #+#    #+#              #
#    Updated: 2021/08/03 20:53:35 by stone            ###   ########.fr        #
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
			ft_split.c \
			ft_calloc.c \
			ft_bzero.c \
			ft_strnstr.c \
			rm_n_first_char.c
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