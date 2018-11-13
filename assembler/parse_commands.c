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

// void	tabs_remover(char *str)
// {
// 	int i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == '\t')
// 			str[i] = ' ';
// 		i++;
// 	}
// }

int		arguments_filler(t_binfile *file, t_lable	*label, t_t *token, char *string, int *i)
{
	char	**str = NULL;
	file->fd = file->fd;
	int		arg1 = 0;

	str = ft_strsplit(string, ' ');
	while (arg1 < g_op_tab[token->c_name].nb_params)
	{
		//printf("%s\n", str[*i]);
		// if (arg1 + 1 != g_op_tab[token->c_name].nb_params && !(ft_strchr(str[*i], ',')))
		// {
		// 	printf("%s\n", "faulty --- fuck:)");
		// 	return (0);
		// }
		// if (arg1 + 1 != g_op_tab[token->c_name].nb_params)
		// 	str[*i][ft_strlen(str[*i]) - 1] = '\0';
		if (str[*i] == '\0')
			return (error_message(token, str[*i]));
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
				return (error_message(token, str[*i + 1]));
			break ;
		}
		(*i)++;
	}
	return (1);
}
int 	line_definer(char *copy)
{
	int l = 0;

	if (ft_strchr(copy, '.'))
		return (1);
	while (copy[l])
	{
		if (!(WHITESPACE(copy[l])))
			return (0);
		l++;
	}
	return (1);
}

int 	count_ns(char *str)
{
	int  i = 0;
	int k = 0;


	while (str[i])
	{
		if (str[i] == '\n')
			k++;
		i++;
	}
	return (k);
}

int		parse_commands(t_binfile *file)
{
	char	**str = NULL;
	char	**str_n = NULL;
	t_t 	*token = NULL;
	char	**copy_n = NULL;

	copy_n = (ft_strsplit(file->copy, '\n'));
	t_lable	*label = NULL;
	int i = 0;
	int n = 0;
	int k = 0;
	file->labels_list = NULL;
	//tabs_remover(file->f_contents);
	str_n = (ft_strsplit(file->f_contents, '\n'));
	while (str_n[n])
	{
		while (copy_n[k] && line_definer(copy_n[k]))
			k++;
		i = 0;
		str = ft_strsplit(str_n[n], ' ');
		if (!(ft_strchr(str[i] ,'%')) && (ft_strchr(str[i], ':')))
		{
			if (label)
			{
				label_length(file, label);
				labels_linker(file, label);
				label = NULL;
			}
			label = (t_lable *)ft_memalloc(sizeof(t_lable));
			label->label_name = label_name_is_valid(file, str[i++]);
			if (label->label_name == NULL)
			{
				printf("Lexical error at [%d:%d]\n", k + 2, 0);
				return (0);
			}
		}
		if (str[i])
		{
			if (!label)
				label = (t_lable *)ft_memalloc(sizeof(t_lable));
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->c_name = command_name(str[i]);
			token->line_num = k;
			token->line_copy = ft_strdup(copy_n[k++]);
			if (command_name(str[i]) == -1)
				return (error_command(token, str[i]));
			token->name_c = ft_strdup(str[i++]);
			token->arguments =  g_op_tab[token->c_name].nb_params; //ft_cmd_arguments(token->name_c);
			token->lbl_size = ft_cmd_lbls(token->name_c);
			token->has_codage = g_op_tab[token->c_name].has_pcode;//has_codage(token->name_c);
			token->opcode = g_op_tab[token->c_name].opcode;
			if (!arguments_filler(file, label, token, str_n[n], &i))
				return (0);
		}
		if (!file->name || !file->comment)
			return (error_message(token, str[0]));
		//printf("%s\n", str_n[n]);
		n++;
		//printf("%s\n", );
		//// delete str to avoid leaks
	}
	if (n != count_ns(file->f_contents) - 1)
	{
		printf ("%s\n", "Syntax error - unexpected end of input (Perhaps you forgot to end with a newline?)");
		return (0);
	}
	if (label != NULL)
	{
		label_length(file, label);
		labels_linker(file, label);
	}
	file_length(file);
	return (1);


}  
