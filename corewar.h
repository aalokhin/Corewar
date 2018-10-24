#ifndef COREWAR_H
# define COREWAR_H

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/get_next_line.h"

# include "op.h"

#define MAGIC_SIZE 1
#define NAME_SIZE 330
#define SIZE_SIZE 10
#define COMMENT_SIZE 5130


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
	unsigned int bots_quantity;
	char *players[4];
} t_flags;

typedef struct s_proc
{
	unsigned int id;
	unsigned int current_position;
	unsigned int carry;
	unsigned int parent_nbr;
	unsigned int regs[REG_NUMBER];
	unsigned int if_live;
	unsigned int cmd;
	int argv[3][2];
	unsigned int cycles_wait;
	struct s_proc *next;
}			t_proc;

static t_proc t_proc7;

typedef struct s_cycle
{
	unsigned int cycles;
	unsigned int processes;
	unsigned int second_limit;
	unsigned int cycle_die;
	unsigned int cycle_delta;
	unsigned char nbr_live;
	unsigned int max_checks;
	unsigned int current_winner;
}			t_cycle;

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

typedef void (*t_cmd)();

void live();
void load();
void store();
void addition();
void substraction();
void bit_and();
void bit_or();
void bit_xor();
void zjmp();
void load_ind();
void store_ind();
void ffork();
void lload();
void lload_ind();
void long_fork();
void aff();


static t_cmd instruct[16] = {&live, &load, &store, &addition, &substraction, &bit_and, &bit_or,
	&bit_xor, &zjmp, &load_ind, &store_ind, &ffork, &lload, &lload_ind,&long_fork, &aff};


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



#endif

