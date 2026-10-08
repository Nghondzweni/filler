# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnghondz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/24 15:59:34 by tnghondz          #+#    #+#              #
#    Updated: 2018/06/24 16:10:13 by tnghondz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= players/tnghondz.filler

RCS_DIR		= ./resources
SRCS		= ./srcs/filler.c
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
INCLUDES	= ./includes

CC			= gcc
CFLAGS		= -Wall -I$(INCLUDES) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	@mkdir -p players
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT_DIR)/get_next_line.c $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
