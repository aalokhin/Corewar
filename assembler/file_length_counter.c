#include "asm.h"


typedef struct			s_op
{
	char				*name;
	int					nb_params;
	int					param_types[4];
	int					opcode;
	int					nb_cycles;
	char				*description;
	int					has_pcode;
	int					has_idx;
}						t_op;


static t_op	g_op_tab[17] =
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


int 	bytes_above_i(t_lable *label)
{
	t_t *tmp;
	int count;


	count = 0;
	tmp = label->instruct;
	while (tmp)
	{
		count += tmp->c_len;
		tmp = tmp->next;
	}
	return (count);
}

void 	bytes_above_filler(t_binfile *file, t_lable *label)
{
	t_lable *tmp;

	label->bytes_above = 0;
	tmp = file->labels_list;
	while (tmp)
	{
		label->bytes_above += tmp->lbl_len;
		tmp = tmp->next;
	}
}

void	token_length(t_t *token, int i, t_lable *label)
{
	token->bytes_above_i = bytes_above_i(label);
	token->c_len = 1;
	token->c_len += token->has_codage;
	while (i < g_op_tab[token->c_name].nb_params)
	{
		token->c_len += token->args[i][0] == 0 ? 0 : token->args[i][0] == 1 ? 1 : token->args[i][0] == 11 ? 2 : token->lbl_size;
		i++;
	}
}


void label_length(t_binfile *file, t_lable	*label)
{
	t_t		*tmp;

	bytes_above_filler(file, label);
	tmp = label->instruct;
	label->lbl_len = 0;
	while (tmp)
	{
		label->lbl_len += tmp->c_len;
		tmp = tmp->next;
	}
}

void	file_length(t_binfile *file)
{
	t_lable	*tmp;

	tmp = file->labels_list;
	file->file_length = 0;
	while (tmp)
	{
		file->file_length += tmp->lbl_len;
		tmp = tmp->next;
	}
}
