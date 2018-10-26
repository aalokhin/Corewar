#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 15:23:08 by vlikhotk          #+#    #+#              #
#    Updated: 2017/11/02 15:15:21 by vlikhotk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = corewar

LIB_DIR = ./libft/

SFILES = main.c vm_cycle.c l_funcs.c funcs_2_9.c init_funcs.c args_parsing.c

OFILES = main.o vm_cycle.o l_funcs.o funcs_2_9.o init_funcs.o args_parsing.o

LIBFT = $(LIBFT_DIR)libftprintf.a
LIBFT_DIR = $(LIB_DIR)
LIBFT_INC = $(LIBFT_DIR)includes/

CC_FLAGS = -Wall -Wextra -Werror 
HEADER_FLAGS = -I $(LIBFT_INC)

CC = gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(CC_FLAGS) $(OFILES) -lncurses $(LIBFT) -o $(NAME)

$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OFILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
