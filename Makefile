# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stone <stone@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 22:23:23 by sdummett          #+#    #+#              #
#    Updated: 2021/08/10 03:25:16 by stone            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ************************************ #
#                                      #
#              VARIABLES               #
#                                      #
# ************************************ #

CC			= clang
CFLAGS		= -Wall -Werror -Wextra
NAME		= pipex
SRC			= pipex.c \
			utils/ft_split.c \
			utils/ft_calloc.c \
			utils/ft_bzero.c \
			utils/ft_strnstr.c \
			utils/ft_strjoin.c \
			rm_n_first_char.c \
			get_paths.c
INC			= -Iincludes
includes	= $(wildcard includes/*.h)
OBJ			= $(SRC:.c=.o)
SRCBONUS	=bonus/pipex_bonus.c \
			bonus/exec_cmd_bonus.c \
			bonus/get_paths_bonus.c \
			bonus/utils/ft_bzero.c \
			bonus/utils/ft_split.c \
			bonus/utils/ft_calloc.c \
			bonus/utils/ft_strjoin.c \
			bonus/utils/ft_strnstr.c \
			bonus/utils/rm_n_first_char.c
OBJBONUS	=$(SRCBONUS:.c=.o)

# ************************************ #
#                                      #
#                RULES                 #
#                                      #
# ************************************ #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJBONUS)
	$(CC) $(CFLAGS) $(OBJBONUS) -o $(NAME)

%.o: %.c $(includes)
	$(CC) $(INC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)
	rm -f $(OBJBONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all