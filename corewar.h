/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:56:08 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/20 18:28:17 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/get_next_line.h"

# include "op.h"
# include <ncurses.h>

# define MAGIC_SIZE 4
# define NULL_SIZE 4
# define EXEC_SIZE 4
# define PRE_EXEC_SIZE (COMMENT_LENGTH + PROG_NAME_LENGTH + MAGIC_SIZE + (NULL_SIZE * 2) + EXEC_SIZE)
# define SEC_LIMIT 50
# define CMD_NBR 16
# define CARETKA 1
# define NO_CARETKA 0

typedef struct		s_proc
{
	int				id;
	int				real_id;
	char			*name;
	int				current_position;
	int				carry;
	int				parent_nbr;
	unsigned int	regs[REG_NUMBER];
	unsigned int	if_live;
	int				lives;
	int				last_live_cycle;
	unsigned char	cmd;
	int				argv[MAX_ARGS_NUMBER - 1][2];
	unsigned int	cycles_wait;
	int				child_proc_lives;
	int				live_cycle;
	int				arg_counter;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_instr
{
	int				i;
	int	one;
	int	two;
	int				new_ind;
	t_proc			*tmp;
}					t_instr;

typedef struct		s_cycle
{
	int				cycles;
	int				processes;
	int				prev_processes;
	int				second_limit;
	int				cycle_die;
	int				current_winner;
	char			*winner_name;
	int				checks_if_die;
	int				prev_cycle_die;
	int				indexes[MEM_SIZE][2];
	int				winner_str;
	int				winner_id;
	int				start_bots;
	int				verbose;
	int				max_id;
	int				shift;
	int				id_counter;
	int				instr_res;
	int				cycle_counter;
	int				fork_ind;
	int				run;
	int				m;
	int				ncurses;
	t_proc			*head_proc;
}					t_cycle;

typedef struct		s_flags
{
	int				i;
	int				j;
	int				a_aff;
	int				d_dumps_memory;
	int				v_verbosity;
	int				ncurses;
	int				pl_nbr[MAX_PLAYERS][2];
	int				bots_quantity;
	char			*players[MAX_PLAYERS];
	int				sum_bots;
	struct s_cycle	main_cycle;
}					t_flags;

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argv[MAX_ARGS_NUMBER - 1];
	int				nbr;
	int				cycles_wait;
	char			*desc;
	int				codage;
	int				label;
	int				arg_nbr;
}					t_op;

typedef void		(*t_cmd)(t_proc *head_proc, int cur_proc,
					t_cycle *main_cycle, unsigned char *map);
typedef void		(*t_aval)(t_proc *processes, unsigned char *map,
					int arg_ind, int *id_counter);

void				live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				load(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				store(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				addition(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				substraction(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				bit_and(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				bit_or(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				bit_xor(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				zjmp(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				load_ind(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				store_ind(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				ffork(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				lload(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
						unsigned char *map);
void				lload_ind(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				long_fork(t_proc *head_proc, int cur_proc,
						t_cycle *main_cycle, unsigned char *map);
void				aff(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
					unsigned char *map);

static t_cmd		g_instruct[REG_NUMBER] = {&live, &load, &store, &addition,
	&substraction, &bit_and, &bit_or, &bit_xor, &zjmp, &load_ind,
	&store_ind, &ffork, &lload, &lload_ind, &long_fork, &aff};

void				get_t_dir_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);
void				get_t_ind_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);
void				get_t_reg_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);

static t_aval		g_get_arg_vals[MAX_ARGS_NUMBER - 1] = {&get_t_reg_value, &get_t_dir_value,
	&get_t_ind_value};

static t_op g_op_tab[CMD_NBR] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 1},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 2},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 2},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 3},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 3},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 3},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 3},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 3},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 3},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 3},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 2},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 3},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 1}
};

void				vm_cycle(unsigned char *map, t_flags *params,
						t_header bots[MAX_PLAYERS]);
void				processes_add(t_proc **processes, unsigned char *map,
						t_cycle *main_cycle, int cur_proc);
void				init_bots(t_header bots[MAX_PLAYERS]);
void				params_init(t_flags *params);
void				main_cycle_init(t_cycle *main_cycle, t_flags *params);
t_proc				*processes_init(t_flags *params, t_header bots[MAX_PLAYERS],
						unsigned char *map);
void				clear_argv_arr(t_proc *processes);
void				get_t_dir_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);
void				get_t_ind_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);
void				get_t_reg_value(t_proc *processes, unsigned char *map,
						int arg_ind, int *id_counter);
void				get_args_values(t_proc *processes, unsigned char *map,
						int *id_counter);
void				take_args(unsigned char codage, t_proc *processes);
void				map_to_screen(unsigned char *map, t_cycle *main_cycle,
						t_flags *params, t_proc *processes, WINDOW *win);
void				visual_init(WINDOW **win, t_flags *params, t_header bots[MAX_PLAYERS]);
void				print_winner(WINDOW *win, t_cycle main_cycle);
int					read_bots(t_flags *params, int fd, t_header	bots[MAX_PLAYERS]);
void				inst_vars_init(t_instr *inst_vars, t_proc *processes);
int					check_ldi_params(t_instr *inst_vars, unsigned char *map);
void				take_bits_params(t_instr *inst_vars, unsigned char *map);
int					if_correct_name(unsigned char *str, t_flags *params, int j);
int					check_magic(unsigned char *str, t_flags *params, int j,
						t_header bots[4]);
int					check_comment(unsigned char *str, t_flags *params, int j);
void				delete_unneeded(t_proc **head, t_cycle *main_cycle);
void				fill_start_map_id(t_cycle *main_cycle, t_header bots[MAX_PLAYERS],
						t_flags *params);
void				intro_print(t_flags *params, t_header bots[MAX_PLAYERS],
						WINDOW **win);
void				after_cycle(t_flags *params, t_header bots[MAX_PLAYERS],
						t_cycle main_cycle);
void				print_adv(t_cycle *main_cycle, t_proc *processes,
						t_flags *params, unsigned char *map);
int					external_cycle_pass(t_cycle *main_cycle, unsigned char *map,
						t_flags *params);
void				print_dump(unsigned char *map);
void				cycle_period_check(int *cycle_counter, t_cycle *main_cycle,
						t_flags *params);
void				music_listener(char spc, t_cycle *main_cycle, WINDOW **win);
void				speed_listener(char spc, t_cycle *main_cycle, WINDOW **win);
void				char_listener(char spc, t_cycle *main_cycle, WINDOW **win);
void				get_args_value(int arg_size, unsigned int *dest, unsigned char *map,
						int *id_counter);
void				create_map(t_header bots[MAX_PLAYERS], t_flags *params);
#endif
