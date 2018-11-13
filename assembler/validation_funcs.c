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
				{
					printf("%s\n", "duplicate labels name");
					return (1);
				}
			}
			tmp = tmp->next;		}
	}
	return (0);
}

char		*label_name_is_valid(t_binfile *file, char *str) /// only label chars copier :)
{
	int		i;
	char	*label_name;

	i = 0;
	if (!(label_name = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] && str[i] != LABEL_CHAR)
	{
		if (!(ft_strchr(LABEL_CHARS, str[i])))
			return (NULL);
		label_name[i] = str[i];
		i++;
	}
	label_name[i] = ':';
	label_name[i + 1] = '\0';
	file->fd = file->fd;
	return (label_name_is_duplicate(file, label_name) ? NULL : label_name);
}

int			arguments_validator(t_binfile *file, t_t *token, char *arg, int i) /// перевіряємо чи існує такий лейбл і чи аргументи співпадають з табличкою  
{
	int		size = 0;
	char	*label_name;
	int		to_count;

 	to_count = g_op_tab[token->c_name].param_types[i];
	size = (ft_strchr(arg ,'r') && !(ft_strchr(arg ,'%'))) ? 1 : ft_strchr(arg ,'%') ? 2 : 4;
	file->fd = file->fd;
 	if (size == to_count || to_count == 7 || (size < to_count && to_count - size != size  && (to_count - size == T_REG
 		|| to_count  - size == T_DIR ||  to_count - size == T_IND)))
 	{
	//printf("%s\n", arg );
 		// if (size == T_REG)
 		// {
 		// 	printf(" === %s\n", arg);
 		// 	if (!arg + 1 || !(ft_isdigit(arg[1])) || ft_atoi(arg + 1)  > 16) /// not sure if needed  reg less than 16 :)
 		// 		return (error_message(token, arg));
 		// }
 		if (ft_strstr(arg, "%:"))
 		{
 			label_name = (char *)ft_memalloc(sizeof(char) * ft_strlen(arg));
 			label_name = arg + 2;
 			label_name[ft_strlen(arg) - 2] = ':';
 			label_name[ft_strlen(arg) - 1] = '\0';
 			if (!(ft_strstr(file->f_contents, label_name)))
 			{
 				label_name[ft_strlen(label_name) - 1] = '\0';
 				return (error_message_label(token, label_name, arg));
 			}
 		}
 		return (1);
 	}
 		return (error_invalid_arg_type(token, i, size));
 	}
//label_exist