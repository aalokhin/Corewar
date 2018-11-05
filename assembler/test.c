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

void			ft_linker(t_binfile *file, t_t 	*token)
{
	t_t		*tmp;

	if (!file->test)
	{
		file->test = token;
		file->test->next = NULL;
	}
	else
	{
		tmp = file->test;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
	}
}
void	printer(t_binfile *file)
{
	t_t		*tmp;

	tmp = file->test;
	while (tmp)
	{
		printf("%s\n", g_op_tab[tmp->c_name].name);
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
		{
			printf("%s\n","digit" );
			return (1);
		}
		i++;
	}
	return (0);
}

void	test(t_binfile *file)
{
	char	**str = NULL;
	t_t 	*token = NULL;
	int i = 0;

	file->test = NULL;
	str = ft_strsplit(file->f_contents, ' '); 
	while (str[i])
	{
		if (ft_strchr(str[i] , '.'))
			printf("%s\n", "name or comment");
		else if (ft_strchr(str[i], ':') && ft_strchr(str[i] ,'%'))
		{
			printf("%s\n", "%:LABEL_used");
		}
		else if (ft_strchr(str[i], ':'))
		{
			if (token != NULL)
				token->label = ft_strdup(str[i]);
			printf("%s\n", "label");
		}
		else if (ft_strchr(str[i] ,'%'))
		{
			printf("%s\n", "%DIGIT");
		}
		else if (ft_strchr(str[i] , ',') || has_digit(str[i]))
		{
			printf("%s\n", "comma");
		}
		else
		{
			printf("%s %s\n", "command == ",str[i]);
			if (token != NULL)
				ft_linker(file, token);
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->c_name = command_name(str[i]); //command_name(str[i]);
		}
		i++;
	}
	printer(file);
}  
