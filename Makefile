# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 00:34:10 by mikhaing          #+#    #+#              #
#    Updated: 2025/08/13 14:08:25 by yiyuli         ###      ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = bsq
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I include 
SRCS =	src/main.c \
		src/read_grid.c \
		src/map_handler.c \
		src/solver.c \
		src/drawing.c \
		src/memory.c \
		utils/ft_atoi.c \
		utils/ft_isnumeric.c \
		utils/ft_isprint.c \
		utils/ft_atol.c \
		utils/ft_isdigit.c \
		utils/ft_memcpy.c \
		utils/ft_putchar_fd.c \
		utils/ft_putstr_fd.c \
		utils/ft_strchr.c \
		utils/ft_strdup.c \
		utils/ft_strjoin.c \
		utils/ft_strlen.c \
		utils/ft_strloc.c \
		utils/ft_strlcpy.c \
		utils/ft_substr.c \
		utils/gnl_node.c \
		utils/gnl.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
