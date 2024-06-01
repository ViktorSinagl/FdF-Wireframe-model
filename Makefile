#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 12:12:15 by vsinagl           #+#    #+#              #
#    Updated: 2024/05/31 14:08:31 by vsinagl          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC:= srcs/main.c \
	get_next_line/get_next_line_bonus.c \
	get_next_line/get_next_line_utils_bonus.c \
	srcs/map.c \
	srcs/utils.c \
	srcs/map_utils.c \
	srcs/image.c \
	srcs/linedraw_dda.c \
	srcs/linedraw_bresemhans.c \
	srcs/draw.c \
	srcs/my_free.c \
	srcs/transformations.c \
	srcs/transformations_utils.c \
	srcs/key_controls.c\

#Flags:
FLAGS:= -Wall -Wextra -Werror
CFLAGS = -I/usr/include -I.mlx_linux -O3
LDFLAGS = -L.mlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Llibft -lft

LIBFT:= libft/libft.a
OBJ := $(SRC:.c=.o)
NAME:= fdf
CC:= clang

#COLORS
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
END = \033[0;39m

#RULES:

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(SRC) $(CFLAGS) -c
	@echo "$(BLUE) c.files compiled with $(RED) clang $(FLAGS) $(BLUE) to object files. $(END)"
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(BLUE) object files linked and executable created "
	@echo "$(GREEN) compilation sucesfull :) $(END)"
	mv *.o objs/
	mv $(OBJ) objs/

$(LIBFT):
	make -C libft/

clean:
	rm objs/*.o

fclean:
	rm $(NAME)

re: clean fclean all

.PHONY: clean fclean re all
