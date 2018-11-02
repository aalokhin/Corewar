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
ASM := asm

LIB_DIR = ./libft/
ASM_DIR = ./assembler/

SFILES = main.c vm_cycle.c l_funcs.c funcs_2_9.c init_funcs.c args_parsing.c visualastia.c

OFILES = main.o vm_cycle.o l_funcs.o funcs_2_9.o init_funcs.o args_parsing.o visualastia.o

ASM_SFILES := ./assembler/main_assembler.c ./assembler/print_errors_usage.c

ASM_OFILES := ./assembler/main_assembler.o ./assembler/print_errors_usage.o

LIBFT = $(LIBFT_DIR)libftprintf.a
LIBFT_DIR = $(LIB_DIR)
LIBFT_INC = $(LIBFT_DIR)includes/

BLUE		=	\033[0;94m
YELLOW		=	\033[0;33m
LIGHT 		= 	\033[0;5m
COLOR_OFF	= 	\033[0m
GREEN 		=  	\033[0;32m
PURPLE 		=	\033[0;35m
CYAN 		= 	\033[0;36m



CC_FLAGS = -Wall -Wextra -Werror -g
HEADER_FLAGS = -I $(LIBFT_INC)

ASSEMBLER_FLAGS = -I .$(LIBFT_INC)

CC = gcc

all: $(NAME) $(ASM)



$(NAME): $(LIBFT) $(OFILES)
	@echo "$(GREEN)compiling libft... ready"
	@echo "$(BLUE)compiling virtual machine..."
	$(CC) $(CC_FLAGS) $(OFILES) -lncurses $(LIBFT) -o $(NAME)
	
	@echo "$(CYAN)Ready!"
	@echo "$(PURPLE)comiling assembler ..."

$(ASM): $(ASM_OFILES)
	@echo "$(PURPLE)comiling assembler ..."
	$(CC) $(CC_FLAGS) $(ASM_OFILES) $(LIBFT) -o $(ASM)
	@echo "$(CYAN)Assembler Ready!"
	@echo "$(COLOR_OFF)"


$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(ASM_OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(ASSEMBLER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OFILES)
	rm -rf $(ASM_OFILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(ASM)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean fcleanlib cleanlib
