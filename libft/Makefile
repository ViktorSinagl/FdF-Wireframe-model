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

SRCS := ft_atoi.c\
			ft_atoi_base.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strstr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c
#filter-out test.c, 
BONUS_S := ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstadd_back.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap_bonus.c

OBJS := $(SRCS:.c=.o)
BONUS_O := $(BONUS_S:.c=.o)
TARGET :=
LIB := libft.a
FLAGS := -Wall -Wextra -Werror
COMPILER:= cc

#COLORS
Black = \033[0;30m
Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m

all: $(LIB)

#target rule, use jost for test.c
$(TARGET): 
	@ $(COMPILER) $(FLAGS) -g $(TARGET).c $(LIB) -o ${TARGET}
	@echo "${Red} $(TARGET) compiled\n"

$(LIB): $(OBJS)
	@ar rc $(LIB) $(OBJS)
	@echo "$(Green) $(LIB) library created!"

$(OBJS): $(SRCS) 
	@ $(COMPILER) $(FLAGS) -c $(SRCS) 
	@echo "$(Magenta) all .c files sucesfully compiled to object files"

clean:
	@rm -f $(OBJS) $(BONUS_O)
	@echo "$(Red) object files removed!"
fclean:
	@rm -f ${LIB}
	@echo "$(Red) library removed!"

re: clean fclean all

bonus: $(BONUS_O) $(OBJS) 
	 ar rc $(LIB) $(OBJS) $(BONUS_O)
	 @echo "$(Yellow) bonus library created!"

$(BONUS_O): $(BONUS_S)
	$(COMPILER) $(FLAGS) -c $(BONUS_S)
	@echo "$(Magenta) BONUS .c files sucesfully compiled to object files"

.PHONY: all clean
