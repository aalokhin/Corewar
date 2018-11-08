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



// void				add_copy_chain(t_chain **head, t_anthill *room)
// {
// 	t_chain			*new;
// 	t_chain			*last;

// 	if (!head)
// 		return ;
// 	new = ft_memalloc(sizeof(t_chain));
// 	new->ngbr = room;
// 	new->next = NULL;
// 	new->nombre = room->name;
// 	new->id = 0;
// 	new->start = room->is_start;
// 	new->end = room->is_end;
// 	if (*head == NULL)
// 	{
// 		new->prev = NULL;
// 		*head = new;
// 		return ;
// 	}
// 	last = *head;
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = new;
// 	new->prev = last;
// }



void			labels_linker(t_binfile *file, t_lable 	*label)
{
	t_lable		*tmp;

	if (!file->labels_list)
	{
		file->labels_list = label;
		file->labels_list->next = NULL;
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

void	token_length(t_t *token, int i) //int 	token_arg_length(t_t *token, int i) by nastia 
{
	token->c_len = 1;
	token->c_len += token->has_codage;
	while (i < 4)
	{

		token->c_len += token->arg[i] == 0 ? 0 : token->arg[i] == 1 ? 1 : token->arg[i] == 11 ? 2 : token->lbl_size;
		i++;
	}
	//printf("token length -- ====== %d\n", token->c_len);
}

void 	length_of_bytes_above(t_binfile *file)
{
	t_lable *tmp;

	tmp = file->labels_list;
	while (tmp)
	{
		tmp->bytes_above += tmp->lbl_len;
		tmp = tmp->next;
	}

}

void label_length(t_binfile *file, t_lable	*label)
{
	t_t		*tmp;

	tmp = label->instruct;
	label->lbl_len = 0;
	length_of_bytes_above(file);
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
	file->file_length  = 0;
	while (tmp)
	{
		file->file_length += tmp->lbl_len;
		tmp = tmp->next;
	}
}

int 	token_codage(t_t *token, int i)
{
	int	dec = 0;
	int k = 128;

	while (i < 4)
	{
		if (token->arg[i] == 11 || token->arg[i] == 10)
			dec += k;
		k /= 2;
		if (token->arg[i] == 11 || token->arg[i] == 1)
			dec += k;
		k /= 2;
		i++;
	}
	return (dec);
}

int 	token_arg_length(t_t *token, int i)
{
	int	byte_len = 1; //opcode + has_codage + args_len

	printf("================================> %d\n", token->lbl_size);
	while (i < 4)
	{
		if (token->arg[i] == 11) 
			byte_len += 2;
		else if (token->arg[i] == 10)
			byte_len += token->lbl_size;
		else if (token->arg[i] == 1)
			byte_len += 1;

		i++;
	}
	byte_len += token->has_codage;
	printf("hhhhhhhhhas coooooooodage %d\n", token->has_codage);
	 printf("\n BYTE_LENGTH ==> %d \n", byte_len);
	token->c_len = byte_len;
	return (token->c_len);
}

void	tabs_remover(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}


// void		lookup_line()
// {
// 	size_t 	k;



// 	k = 0;
// 	if (!(ft_strchr(str[i] ,'%')) && (ft_strchr(str[i], ':')))
// 	{
// 		if (label != NULL)
// 		{
// 			label_length(file, label);
// 			labels_linker(file, label);
// 			label = NULL;
// 		}
// 		label = (t_lable *)ft_memalloc(sizeof(t_lable));
// 		label->label_name = ft_strdup(str[i]);
// 	}

// }

// void 		parse_commands(t_binfile *file)
// {
// 	char	**parse	 = NULL;
// 	t_t 	*token;
// 	t_lable	*label;
// 	size_t i = 0;
// 	size_t k = 0; 

// 	token = NULL;
// 	label = NULL;

// 	parse = ft_strsplit(file->f_contents, '\n');
// 	while(parse[i])
// 	{
// 		if (ft_strcmp(parse[i], "\n") == 0) //kostyl first empty line
// 			printf("empty line\n");

// 		i++;
// 	}
// 	size_t length;

// 	length = i;
// 	i = 0;

// 	char	**str = NULL;
// 	while(i < length)
// 	{
// 		if (ft_strcmp(parse[i], "\n"))
// 			continue; 
// 		str = ft_strsplit(parse[i], ' ');
		

// 		printf("line is: [%s]\n", parse[i]);
// 		ft_clean_parse(str);
// 		i++;
// 	}
// 	ft_clean_parse(parse);
// }



void	parse_commands(t_binfile *file)
{
	char	**str = NULL;
	t_t 	*token = NULL;

	t_lable	*label = NULL;
	int i = 0;
	int arg1 = 0;
	file->labels_list = NULL;
	tabs_remover(file->f_contents);
	str = ft_strsplit(file->f_contents, ' ');
	while (str[i])
	{
		if (!(ft_strchr(str[i] ,'%')) && (ft_strchr(str[i], ':')))
		{
			if (label != NULL)
			{
				label_length(file, label);
				labels_linker(file, label);
				label = NULL;
			}
			label = (t_lable *)ft_memalloc(sizeof(t_lable));
			label->label_name = ft_strdup(str[i]);
		}
		else if (!token || (token && arg1 == token->arguments))
		{
			if (!label)
				label = (t_lable *)ft_memalloc(sizeof(t_lable));
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->c_name = command_name(str[i]);
			token->name_c = ft_strdup(str[i]);
			token->arguments = ft_cmd_arguments(token->name_c);
			token->lbl_size = ft_cmd_lbls(token->name_c);
			token->has_codage = has_codage(token->name_c);
			//printf(" command: [%s] ===> ft_cmd_arguments : ===>%d and cmd_label is : %d  and has_codage is [%d]\n ",
	//token->name_c, token->arguments, token->lbl_size, token->has_codage);
		}
		else
		{

			if (ft_strchr(str[i] ,'r') && !(ft_strchr(str[i] ,'%')))
				token->arg[arg1] = 1;
			else if (ft_strchr(str[i] ,'%'))
				token->arg[arg1] = 10;
			else
				token->arg[arg1] = 11;
			token->a[arg1++] = ft_strdup(str[i]);
			if (arg1 == token->arguments)
			{
				command_linker(label, token);
				if (token->has_codage)
					token->codage = token_codage(token, 0);
				token_length(token, 0);
				token_arg_length(token, 0);
				arg1  = 0;
				token = NULL;
			}
			//printf("DONE\n");
		}
		i++;
	}
	if (label != NULL)
	{
		labels_linker(file, label);
		label_length(file, label);
		label = NULL;
	}
	//labels_printer(file);
	file_length(file);
	printf("length of this file DECIMAL === %d HEX  === %x\n", file->file_length, file->file_length);

	
	// printf("pkokokokokok\n");
	// int f = 0;

	// char	*arguments[3] = {"r1", "%0", "r1"};
	// // r1, %0, r1
	// int z = 0;
	// f = 7;
	// while(z < 3)
	// {
		
	// 	if (ft_strchr(arguments[z] ,'r') && !(ft_strchr(arguments[z] ,'%')))
	// 	{
	// 		f--;
	// 		printf("f1 ==> %d\n", f);

	// 		my_cod |= 1 << f;
	// 		f -= 1;
	// 		printf("f1 ==> %d\n", f);

	// 	}
	// 	else if (ft_strchr(arguments[z] ,'%'))
	// 	{
	// 		printf("f2 ==> %d\n", f);

			
	// 		my_cod |= 1 << f;
	// 		f -= 2;
	// 		printf("f2 ==> %d\n", f);

	// 	}
	// 	else
	// 	{
	// 		printf("f3 ==> %d\n", f);	
	// 		my_cod |= 1 << f;
	// 		f--;
	// 		my_cod |= 1 << f;
	// 		f-= 2;
	// 		printf("f3 ==> %d\n", f);

	// 	}
	// 	z++;
	// }
	// printf("codage===================> [%x]\n", my_cod);

}  




