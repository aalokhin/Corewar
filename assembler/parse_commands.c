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

int  command_name(char *name)
{
	 int     i;

	 i = 0;
	 while (g_op_tab[i].name)
	 {
		if ((ft_strcmp(g_op_tab[i].name, name) == 0))
			return (i);
		i++;
	 }
	 return (-1);
}

void			labels_linker(t_binfile *file, t_lable 	*label)
{
	t_lable		*tmp;

	if (!file->labels_list)
	{
		file->labels_list = label;
		file->labels_list->next = NULL;
	}
	else
	{
		tmp = file->labels_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = label;
	}
}

void			command_linker(t_lable 	*label, t_t 	*token)
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

void	command_printer(t_lable *label)
{
	t_t *tmp;

	tmp = label->instruct;
	while (tmp)
	{
		printf(" COMMAND == %s ", g_op_tab[tmp->c_name].name);
		printf("Arguments = %d %d %d %d\n", tmp->arg[0], tmp->arg[1], tmp->arg[2], 00);
		printf("Arguments =  %s %s %s\n", tmp->a[0], tmp->a[1], tmp->a[2]);
		tmp = tmp->next;
	}
}

void	labels_printer(t_binfile *file)
{
	t_lable		*tmp;

	tmp = file->labels_list;
	while (tmp)
	{
		printf("LABEL ==== %s ", tmp->label_name);
		command_printer(tmp);
		tmp = tmp->next;
	}
}

int		has_digit(char *str)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if (ft_strchr(str, '0' + i))
			return (1);
		i++;
	}
	return (0);
}

// T_REG r 01 T_DIR % 10 T_IND 11
// int	 	arguments_filler()
void	parse_commands(t_binfile *file)
{
	char	**str = NULL;
	t_t 	*token = NULL;
	t_lable	*label = NULL;
	int i = 0;
	int arg1 = 0;

	file->labels_list = NULL;
	str = ft_strsplit(file->f_contents, ' ');
	while (str[i])
	{
		if (!(ft_strchr(str[i] ,'%')) && (ft_strchr(str[i], ':')))
		{
			if (label != NULL)
				labels_linker(file, label);
			label = (t_lable *)ft_memalloc(sizeof(t_lable));
			label->label_name = ft_strdup(str[i]);
		}
		else if (!token || (token && arg1 == token->arguments))
		{
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->c_name = command_name(str[i]);
			token->arguments = ft_cmd_arguments(str[i]);
			token->lbl = ft_cmd_lbls(str[i]);
			printf("\n command: [%s] ===> ft_cmd_arguments : ===>%d and cmd_label is : %d \n ", str[i], token->arguments, token->lbl);
		}
		else
		{
			if (ft_strchr(str[i] ,'r'))
				token->arg[arg1] = 01;
			else if (ft_strchr(str[i] ,'%'))
				token->arg[arg1] = 10;
			else
				token->arg[arg1] = 11;
			token->a[arg1++] = ft_strdup(str[i]);
			if (arg1 == token->arguments)
			{
				command_linker(label, token);
				arg1  = 0;
				token = NULL;
			}
		}
		i++;
	}
	if (label != NULL)
		labels_linker(file, label);
	labels_printer(file);
}  
