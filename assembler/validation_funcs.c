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

int			label_name_is_duplicate(t_binfile *file, char *label_name)
{
	t_lable	*tmp;
	if (file->labels_list)
	{
		tmp = file->labels_list;
		while (tmp)
		{
			if (tmp->label_name)
			{
				if (!(ft_strcmp(tmp->label_name, label_name)))
					return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int 	label_name_is_valid(t_binfile *file, t_lable *label, char *str)
{
	int		i;
	char	*label_name;

	i = 0;
	if (!(label_name = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	while (str[i] && str[i] != LABEL_CHAR)
	{
		if (!(ft_strchr(LABEL_CHARS, str[i])))
			return (0);
		label_name[i] = str[i];
		i++;
	}
	label_name[i] = ':';
	label_name[i + 1] = '\0';
	if (label_name_is_duplicate(file, label_name))
	{
		//printf("Lexical error at [%d:%d]\n", label->line_num, define_line_colomn(file, str, label->line_num));
		printf("%s\n", "duplicate label");
		return (0);
	}
	label->label_name = label_name;
	return (1);
}

int 		all_digits(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}


int			arguments_validator(t_binfile *file, t_t *token, char *arg, int i)
{
	int		size = 0;
	int		to_count;

 	to_count = g_op_tab[token->c_name].param_types[i];
	size = (ft_strchr(arg ,'r') && !(ft_strchr(arg ,'%'))) ? 1 : ft_strchr(arg ,'%') ? 2 : 4;
 	if (size == to_count || to_count == 7 || (size < to_count && to_count - size != size  && (to_count - size == T_REG
 		|| to_count  - size == T_DIR ||  to_count - size == T_IND)))
	{
 		// if (size == T_REG)
 		// 	if (!(arg + 1) || !(ft_isdigit(arg[1])) || !all_digits(arg + 1) || arg[1] != '-')
 		// 		return (error_message(file, arg, token->line_num));
 		if (ft_strstr(arg, "%:"))
 		{
 			if (!(ft_strstr(file->f_contents, arg + 2)))
 			{
 				printf("%s\n", "we are herer" );
 				//label_name[ft_strlen(label_name) - 1] = '\0';
 				return (0);//error_message_label(file, token, arg + 2, arg));
 			}
 			return (1);
 		}
 		// if (size == T_DIR)
 		// 	 if (!(arg + 1) || !(ft_isdigit(arg[1])) || !all_digits(arg + 1) || arg[1] != '-' )
 		// 		return (error_message(file, arg, token->line_num));
 		// if (size == T_IND)
 		// {
 		// 	 if (!all_digits(arg) || arg[0] != '-')
 		// 		return (error_message(file, arg, token->line_num));
 		// }
 		// else
 			return (1);
	 }
 	return (error_invalid_arg_type(token, i, size));
}

char *string_definer(char *str, int i)
{
	int k = i;
	int l = 0;
	char *string;

	while (str[i] && str[i] != '\n')
		i++;
	string  = (char *)ft_memalloc(sizeof(char) * (i - k + 1));
	while (str[k] && str[k] != '\n')
	{
		string[l] = str[k];
		l++;
		k++;
	}
	string[l] = '\0';
	return (string);
}

int 	initial_validation(t_binfile *file)
{
	char	*str;
	char 	cpy[2];
	int 	line = 0;
	int 	colomn = 0;

	int i = 0;
	int start = 0;
	str = file->f_contents;
	while (str[i])
	{
		if (str[i] == '\n')
			start = i;
		if (!(WHITESPACE(str[i])) && str[i] != '-' && !ft_isdigit(str[i]) && str[i] != '_' && (str[i] < 97 ||  str[i] > 123) && str[i] != ':' && str[i] != '%' && str[i] != ',')
		{
			cpy[0] = str[i];
			cpy[1] = '\0';
			line = define_line_num(file->copy, string_definer(str, start + 1), 0, 0);
			colomn = define_line_colomn(file->copy, cpy, line);
			printf ("Lexical error at [%d:%d]\n", line + 1, colomn);
			return (0);
		}
		i++;
	}
	return (1);
}
//label_exist