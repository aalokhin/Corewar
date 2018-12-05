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


int		arguments_filler(t_binfile *file, t_t *token, char **str, int *i)
{
	int		arg1;

	arg1 = 0;
	while (arg1 < g_op_tab[token->c_name].nb_params && str[*i])
	{
		if (!(arguments_validator(file, token, str[*i], arg1)))
 			return (0);
		token->args[arg1][0] = (ft_strchr(str[*i] ,'r') && !(ft_strchr(str[*i] ,DIRECT_CHAR)))
	&& !(ft_strchr(str[*i] ,LABEL_CHAR)) ? 1 : ft_strchr(str[*i] ,DIRECT_CHAR) ? 10 : 11;
		token->a[arg1++] = ft_strdup(str[*i]);
		if (arg1 == g_op_tab[token->c_name].nb_params)
		{
			if (str[*i + 1])
				return (error_invalid_arg_type(token, *i, (ft_strchr(str[*i + 1] ,'r')
					&& !(ft_strchr(str[*i + 1] ,DIRECT_CHAR))) && !(ft_strchr(str[*i + 1] ,LABEL_CHAR))
					? 1 : ft_strchr(str[*i + 1] ,DIRECT_CHAR) ? 2 : 3));
			break ;
		}
		(*i)++;
	}
	if (arg1 != g_op_tab[token->c_name].nb_params)
		return (error_invalid_arg_type(token, *i, 3));
	return (1);
}
char	*space_adder(char **str)
{
	char	*cmd;
	char 	*cpy;
	int		i;

	i = 0;
	cpy = *str;
	while (cpy[i])
	{
		if (cpy[i] == DIRECT_CHAR || cpy[i] == LABEL_CHAR)
			break ;
		i++;
	}
	cmd = ft_strsub(cpy, 0, i);
	*str = ft_strsub(cpy, i, ft_strlen(cpy));
	ft_strdel(&cpy);
	return (cmd);
}

int 	clean(char **str, char **str_n)
{
	ft_clean_parse(str);
	ft_clean_parse(str_n);
	return (0);
}

int 	fill_command_name(t_binfile *file, t_t *token, char **str, int *i)
{
	char *copy =  NULL;

	if (ft_strchr(*str, DIRECT_CHAR) || ft_strchr(*str, LABEL_CHAR))
	{
		copy = space_adder(str);
		if (command_name(copy, token) == -1)
		{
			error_command(file, copy, token->line_num);
			ft_strdel(&copy);
			return (0);
		}
		ft_strdel(&copy);
		*i -= 1; 
	}
	else if (command_name(*str, token) == -1)
	{
		error_command(file, *str, token->line_num);
		return (0);
	}
	return (1);
}

int		parse_commands(t_binfile *file, int k, char **str, char **str_n)
{
	t_t 	*token = NULL;
	t_lable	*label = NULL;
	int i = 0;

	str_n = (ft_strsplit(file->f_contents, '\n'));
	while (str_n[k])
	{
		i = 0;
		str = ft_strsplit(str_n[k], ' ');
		if (!file->name || !file->comment)
		{
			error_message(file, str[i], define_line_num(file->copy, str[i], 0, 0));
			return (clean(str, str_n));
		}
		if (i == 0 && !(ft_strchr(str[i], DIRECT_CHAR)) && (ft_strchr(str[i], LABEL_CHAR)))
		{
			if (label)
				label = labels_linker(file, label);
			label = (t_lable *)ft_memalloc(sizeof(t_lable));
			if (!(label_name_is_valid(file, label, str[i++])))
			{
				labels_linker(file, label);
				return (clean(str, str_n));
			}
		}
		if (str[i])
		{
			if (!label)
				label = (t_lable *)ft_memalloc(sizeof(t_lable));
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->line_num = define_line_num(file->copy, str_n[k], 0, 0);
			if ((!fill_command_name(file, token, &(str[i]), &i)) || (++i >= 0 && (!arguments_filler(file, token, str, &i))))
			{
				command_linker(label, token);
				labels_linker(file, label);
				return (clean(str, str_n));
			}
			if (token->has_codage)
				token->codage = token_codage(token, 0);
			command_linker(label, token);
			token_length(token, 0, label);
		}
		ft_clean_parse(str);
		k++;
	}
	if (label)
		labels_linker(file, label);
	ft_clean_parse(str_n);
	file_length(file);
	return (1);
}  
