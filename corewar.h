#ifndef COREWAR_H
# define COREWAR_H

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/get_next_line.h"

# include "op.h"
# include <ncurses.h>

#define MAGIC_SIZE 1
#define NAME_SIZE 330
#define SIZE_SIZE 10
#define COMMENT_SIZE 5130

typedef struct s_proc
{
	int id;
	int real_id;
	char *name;
	int current_position;
	int carry;
	int parent_nbr;
	unsigned int regs[REG_NUMBER];
	unsigned int if_live;
	int lives;
	int last_live_cycle;
	unsigned char cmd;
	int argv[3][2];
	unsigned int cycles_wait;
	int child_proc_lives;
	int live_cycle;
	struct s_proc *next;
}			t_proc;

typedef struct s_cycle
{
	int cycles;
	int processes;
	int prev_processes;
	int second_limit;
	int cycle_die;
	int current_winner;
	char *winner_name;
	int checks_if_die;
	int prev_cycle_die;
	int indexes[MEM_SIZE][2];
	int winner_str;
	int winner_id;
	int start_bots;
	int verbose;
	t_proc *head_proc;
}			t_cycle;

typedef struct s_flags
{
	int a_aff;
	int d_dumps_memory;
	int s_cycles;
	int v_verbosity;
	int binary;
	int b_stealth;
	int ncurses;
	int n_stealth;
	int pl_nbr[4][2];
	int bots_quantity;
	char *players[4];
	struct s_cycle main_cycle;
} t_flags;

typedef struct s_op
{
	char				*name;
	int					argc;
	t_arg_type			argv[3];
	int					nbr;
	int					cycles_wait;
	char				*desc;
	int					codage;
	int					label;
}			t_op;

typedef int (*t_cmd)(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
typedef void (*t_aval)(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);

int live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int load(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int store(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int addition(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int substraction(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int bit_and(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int bit_or(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int bit_xor(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int zjmp(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int load_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int store_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int ffork(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int lload(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int lload_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int long_fork(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);
int aff(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map);


static t_cmd instruct[16] = {&live, &load, &store, &addition, &substraction, &bit_and, &bit_or,
	&bit_xor, &zjmp, &load_ind, &store_ind, &ffork, &lload, &lload_ind,&long_fork, &aff};

void get_t_dir_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);
void get_t_ind_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);
void get_t_reg_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);

static t_aval get_arg_vals[3] = {&get_t_reg_value, &get_t_dir_value, &get_t_ind_value};

static t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};


void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4]);
int find_arg_index(t_proc *processes, int target);
void processes_add(t_proc **processes, unsigned char *map, t_cycle *main_cycle, int index, int cur_proc);
void init_bots(header_t bots[4]);
void params_init(t_flags *params);
void main_cycle_init(t_cycle *main_cycle, t_flags *params);
t_proc * processes_init(t_flags *params, header_t bots[4], unsigned char *map);
void clear_argv_arr(t_proc *processes);
void get_t_dir_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);
void get_t_ind_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);
void get_t_reg_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter);
void get_args_values(t_proc *processes, unsigned char *map, int *id_counter);
void take_args(unsigned char codage, t_proc *processes);
void map_to_screen(unsigned char *map, t_cycle *main_cycle, t_flags *params, t_proc *processes, WINDOW *win);
void visual_init(WINDOW **win);
void print_winner(WINDOW * win, t_cycle main_cycle);

#endif

