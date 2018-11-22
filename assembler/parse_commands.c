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

int 	token_codage(t_t *token, int i)
{
	int	dec = 0;
	int k = 128;

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

int		arguments_filler(t_binfile *file, t_lable *label, t_t *token, char **str, int *i)
{
	int		arg1 = 0;

	while (arg1 < g_op_tab[token->c_name].nb_params)
	{
		if (str[*i] == '\0')
			return (error_message(file, str[*i], token->line_num));
		if (!(arguments_validator(file, token, str[*i], arg1)))
 			return (0);
		token->args[arg1][0] = (ft_strchr(str[*i] ,'r') && !(ft_strchr(str[*i] ,'%'))) ? 1 : ft_strchr(str[*i] ,'%') ? 10 : 11;
		token->a[arg1++] = ft_strdup(str[*i]);
		if (arg1 == g_op_tab[token->c_name].nb_params)
		{
			command_linker(label, token);
			if (token->has_codage)
				token->codage = token_codage(token, 0);
			token_length(token, 0, label);
			if (str[*i + 1])
				return (error_message(file, str[*i + 1], token->line_num));
			break ;
		}
		(*i)++;
	}
	return (1);
}

int		parse_commands(t_binfile *file, int i, char **str, char **str_n)
{
	t_t 	*token = NULL;
	t_lable	*label = NULL;

	str_n = (ft_strsplit(file->f_contents, '\n'));
	while (*str_n)
	{
		i = 0;
		str = ft_strsplit(*str_n, ' ');
		if (!(ft_strchr(str[i] ,'%')) && (ft_strchr(str[i], ':')))
		{
			if (label)
				label = labels_linker(file, label);;
			label = (t_lable *)ft_memalloc(sizeof(t_lable));
			label->line_num = define_line_num(file->copy, *str_n, 0, 0);
			if (!file->name || !file->comment)
				return (error_message(file, str[0], label->line_num));
			if (!(label_name_is_valid(file, label, str[i++])))
				return (0);
		}
		if (str[i])
		{
			if (!label)
			{
				label = (t_lable *)ft_memalloc(sizeof(t_lable));
				label->line_num = define_line_num(file->copy, *str_n, 0, 0);
			}
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->line_num = define_line_num(file->copy, *str_n, 0, 0);
			if (!file->name || !file->comment)
				return (error_message(file, str[0], label->line_num));
			if (command_name(str[i], token) == -1)
				return (error_command(file, str[i], token->line_num));
			if (++i && (!arguments_filler(file, label, token, str, &i)))
				return (0);
		}
		ft_clean_parse (str); /// cleaning
		ft_strdel(&(*str_n)); /// cleaning 
		str_n++;
	}
	if (label)
		labels_linker(file, label);
	file_length(file);
	system("leaks asm");
	return (1);
}  
