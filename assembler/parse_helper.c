
#include "asm.h"

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


int 	token_codage(t_t *token, int i)
{
	int	dec;
	int k;

	dec = 0;
	k = 128;
	while (i < 4)
	{
		if (token->args[i][0] == 11 || token->args[i][0] == 10)
			dec += k;
		k /= 2;
		if (token->args[i][0] == 11 || token->args[i][0] == 1)
			dec += k;
		k /= 2;
		i++;
	}
	return (dec);
}

int  command_name(char *name, t_t *token)
{
	token->c_name = 0;

	while (g_op_tab[token->c_name].name)
	{
		if ((ft_strcmp(g_op_tab[token->c_name].name, name) == 0))
		{
			token->name_c = ft_strdup(name);
			token->arguments =  g_op_tab[token->c_name].nb_params;
			token->lbl_size = ft_cmd_lbls(token->name_c);
			token->has_codage = g_op_tab[token->c_name].has_pcode;
			token->opcode = g_op_tab[token->c_name].opcode;
			return (token->c_name);
		}
		token->c_name++;
	}
	return (-1);
}

t_lable		*labels_linker(t_binfile *file, t_lable *label)
{
	t_lable		*tmp;

	if (!file->labels_list)
	{
		file->labels_list = label;
		file->labels_list->prev = NULL;
	}
	else
	{
		tmp = file->labels_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = label;
		label->prev = tmp;
	}
	label_length(file, label);
	return (NULL);
}

void			command_linker(t_lable *label, t_t *token)
{
	t_t		*tmp;

	if (!label->instruct)
	{
		label->instruct = token;
		label->instruct->next = NULL;
	}
	else
	{
		tmp = label->instruct;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
	}
}
