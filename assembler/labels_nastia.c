#include "asm.h"
	
// void		fill_instruction_arg(t_lable *lable, t_t *instruct, t_arg 	*new)
// {
// 	t_lable *tmp;
// 	t_t 	*instruct1;
// 	int 	dist_dif;
// 	char 	*search;
// 	new->distance = 0;

// 	tmp = lable;
// 	instruct1 = instruct;
// 	dist_dif = 0;
// 	if (ft_strstr(new->line, "%:"))
// 	{
// 		search = ft_strstr(new->line, "%:") + 2;
// 		printf("==============> %s\n", search);
// 		new->is_dir = 1;
// 		while(tmp->prev)
// 		{
// 			if (ft_strcmp(tmp->label_name, search) == 0)
// 				new->distance = lable->bytes_above - tmp->bytes_above;
// 			tmp = tmp->prev;
// 		}
// 		tmp = lable;
// 		while (tmp->next)
// 		{
// 			if (ft_strcmp(tmp->label_name, search) == 0)
// 				new->distance = lable->bytes_above - tmp->bytes_above;
// 			tmp = tmp->next;
// 		}

// 		// new->distance = 
// 	}
// }


// void	instruction_linker(t_t *command, t_arg *new)
// {
// 	t_arg		*tmp;

// 	if (!command->inst)
// 	{
// 		command->inst = new;
// 		command->inst->next = NULL;
// 	}
// 	else
// 	{
// 		tmp = command->inst;
// 		while(tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}

// }


// void 	fill_arguments_array(t_binfile *bin)
// {

// 	t_lable *tmp;
// 	t_t		*tmpi;	
// 	t_arg 	*new;
// 	int 	k;


// 	tmp = bin->labels_list;
// 	while(tmp)
// 	{
	
// 		tmpi = tmp->instruct;

// 		while(tmpi)
// 		{
// 			k = 0;
// 			while(k < tmpi->inst_nbr)
// 			{
// 				new = (t_arg *)ft_memalloc(sizeof(t_arg));
// 				new->line = ft_strdup(tmpi->a[k]);
// 				fill_instruction_arg(tmp, tmpi, new);
// 				instruction_linker(tmpi, new);
// 				new = NULL;
// 				k++;
// 			}

// 			tmpi = tmpi->next;
// 		}
// 		tmp = tmp->next;
// 	}


// 	tmp = bin->labels_list;

// 	printf("PRINTING ARG ARRAY FOR CHECKING\n");

// 	while(tmp)
// 	{
// 		printf("label %s\n", tmp->label_name);
// 		tmpi = tmp->instruct;
// 		while(tmpi)
// 		{
// 			printf(" INSTRUCTION	[%s] WITH ARGS: \n", tmpi->name_c);
// 			new = tmpi->inst;
// 			while (new)
// 			{
// 				printf(" =>(%s)<=", new->line);
// 				if (new->is_dir)
// 					printf("NEW distance >>%d<<", new->distance);
// 				printf("\n");

// 				new = new->next;
// 			}
// 			tmpi = tmpi->next;
// 		}
// 		tmp = tmp->next;
// 	}


// }
//bee_gees
// 0b 68 01 00 45 00 01
// 0b 68 01 00 22 00 01 
// 02 90 00 00 00 01 03
// 02 90 00 00 00 21 06
// 04 54 02 03 02
// 08 64 02 00 00 00 0f 04 
// live 2
// 01 00 00 00 04 
// 09 00 10 
// 0c ff eb 
// 02 90 00 00 00 00 04
// 09 ff e1 
// 02 90 00 00 00 00 04 
// 01 00 00 00 04 
// 09 ff fb

int 		find_arg_value(t_binfile *bin, char *str, t_t *instruct, t_lable *label)
{
	char 		*search;
	t_lable		*tmp_lbl;

	tmp_lbl = bin->labels_list;
	if (ft_strstr(str, "%:"))
	{
		search = ft_strstr(str, "%:") + 2;
		while(tmp_lbl)
		{
			if (tmp_lbl->label_name)
			{
				if (strcmp(search, tmp_lbl->label_name) == 0)
				{
					if (label->bytes_above < tmp_lbl->bytes_above)
					{
						printf("\n\n~~~~~~~~~~~~~~~.1st case %d\n", tmp_lbl->bytes_above - label->bytes_above - instruct->bytes_above_i);
						printf("		===>%d\n", instruct->bytes_above_i);
						return (tmp_lbl->bytes_above - label->bytes_above - instruct->bytes_above_i);
					}
					else
					{
						printf("\n\n~~~~~~~~~~~~~~~~2ND case %d\n", tmp_lbl->bytes_above - label->bytes_above - instruct->bytes_above_i);
						return (tmp_lbl->bytes_above - (label->bytes_above +  instruct->bytes_above_i));
					}
				}
			}
			tmp_lbl = tmp_lbl->next;
		}
		
	}
	return (ft_strstr(str, "r") ? ft_atoi(ft_strstr(str, "r") + 1) : ft_atoi(ft_strstr(str, "%") + 1));
}

void	label_distance(t_binfile 	*bin)
{
	int k;
	t_lable *tmp;
	t_t		*tmpi;	

	tmp = bin->labels_list;
	while(tmp)
	{
	
		tmpi = tmp->instruct;
		printf(" === label  name is: {%s} with %d bytes_above) ===\n", tmp->label_name, tmp->bytes_above);
		k = 0;
		while(tmpi)
		{
			k = 0;
			printf("	=>instruction  is: %s (opcode %d) and it's size  %d\n", tmpi->name_c, tmpi->opcode,  tmpi->c_len);
			// printf("				args: ");
			while(tmpi->a[k])
			{
				printf("{%s} ", tmpi->a[k]);
				tmpi->args[k][1] = find_arg_value(bin, tmpi->a[k], tmpi, tmp);
				printf(" argument {%s}       ---  distance in dec  %d in hex  %x\n", tmpi->a[k], tmpi->args[k][1], tmpi->args[k][1]);
				k++;
			}
			tmpi = tmpi->next;
			printf("\n");
		}
		tmp = tmp->next;
	}
}

