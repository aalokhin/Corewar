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

SFILES = ./v_machine/main.c ./v_machine/vm_cycle.c ./v_machine/ldi_funcs.c ./v_machine/live_mat_jump.c ./v_machine/s_funcs.c \
./v_machine/init_funcs.c ./v_machine/args_parsing.c ./v_machine/visualastia.c ./v_machine/read_bots.c ./v_machine/forks_aff.c \
./v_machine/bits_instr.c ./v_machine/bots_parsing.c ./v_machine/lld_funcs.c ./v_machine/fill_delete_funcs.c \
./v_machine/print_in_cycle.c ./v_machine/check_lives.c

OFILES = ./v_machine/main.o ./v_machine/vm_cycle.o ./v_machine/ldi_funcs.o ./v_machine/live_mat_jump.o ./v_machine/s_funcs.o \
./v_machine/init_funcs.o ./v_machine/args_parsing.o ./v_machine/visualastia.o ./v_machine/read_bots.o ./v_machine/forks_aff.o \
./v_machine/bits_instr.o ./v_machine/bots_parsing.o ./v_machine/lld_funcs.o ./v_machine/fill_delete_funcs.o \
./v_machine/print_in_cycle.o ./v_machine/check_lives.o

ASM_SFILES := ./assembler/file_length_counter.c  ./assembler/a_printing.c ./assembler/a_flag_output_funcs.c \
./assembler/validation_funcs.c ./assembler/labels_nastia.c ./assembler/main_assembler.c ./assembler/print_errors_usage.c \
./assembler/encoding_funcs.c ./assembler/output_to_file.c ./assembler/parse_file_funcs.c  ./assembler/parse_commands.c \
./assembler/commands_help_funcs.c ./assembler/errors_manager.c 

ASM_OFILES :=  ./assembler/file_length_counter.o ./assembler/a_printing.o ./assembler/a_flag_output_funcs.o \
./assembler/validation_funcs.o ./assembler/labels_nastia.o ./assembler/main_assembler.o \
./assembler/print_errors_usage.o  ./assembler/encoding_funcs.o ./assembler/output_to_file.o ./assembler/parse_file_funcs.o \
./assembler/parse_commands.o ./assembler/commands_help_funcs.o ./assembler/errors_manager.o

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

CC = @gcc 

all: $(NAME) $(ASM)

$(NAME): $(LIBFT) $(OFILES)
	@echo "$(BLUE)compiling virtual machine..."
	$(CC) $(CC_FLAGS) $(OFILES) -lncurses $(LIBFT) -o $(NAME)
	@echo "$(BLUE)Ready!"
	@echo "$(PURPLE)comiling assembler ..."

$(ASM): $(ASM_OFILES)
	@echo "$(PURPLE)comiling assembler ..."
	$(CC) $(CC_FLAGS) $(ASM_OFILES) $(LIBFT) -o $(ASM)
	@echo "$(PURPLE)Assembler Ready!$(COLOR_OFF)"


$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(ASM_OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(ASSEMBLER_FLAGS)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(CYAN)Cleaning garbage..."
	@rm -rf $(OFILES)
	@rm -rf $(ASM_OFILES)
	@make clean -C $(LIBFT_DIR)
	@echo "$(CYAN)All clean"


fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(ASM)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean fcleanlib cleanlib