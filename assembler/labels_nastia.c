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



int 		find_arg_value(t_binfile 	*bin, char *str, t_t *instruct, t_lable *lable)
{

	char 		*search;
	t_lable		*tmp_lbl;
	int 		ret;
	int 		byte_len;

	ret = 0;

	tmp_lbl = bin->labels_list;
	bin->arg_length = bin->arg_length;
	byte_len = instruct->lbl_size;
	//printf("~~~~~~~~~~~~~~~~~~~~~%s\n", lable->label_name);
	if (ft_strstr(str, "%:"))
	{
		search = ft_strstr(str, "%:") + 2;
		while(tmp_lbl)
		{
			if (strcmp(search, tmp_lbl->label_name) == 0)
			{
				if (lable->bytes_above < tmp_lbl->bytes_above)
					ret = tmp_lbl->bytes_above - lable->bytes_above;
				else
					ret = tmp_lbl->bytes_above - bin->file_length + instruct->c_len;
				// printf("lable name [%s]", tmp_lbl->label_name);
				// printf("\n\ncurrent: %d\n", lable->bytes_above);
				// printf("tmp: %d\n", tmp_lbl->bytes_above);
				printf("===================================> return : %d", ret);
			}
			tmp_lbl = tmp_lbl->next;
		}
		
		// printf("********************%s\n", search);


	}
	return (ret);

}

void	label_distance(t_binfile 	*bin)
{
	
	bin->champ_size_nbr = 0;
	
	int k;


	t_lable *tmp;
	t_t		*tmpi;	

	tmp = bin->labels_list;


	// tmp = bin->labels_list; //****************************** bytes above ***********
	// while(tmp)
	// {
	// 	if (!tmp->prev)
	// 		tmp->bytes_above = 0;
	// 	else
	// 		tmp->bytes_above = tmp->prev->lbl_len;
	// 	tmp = tmp->next;
	// }

	// tmp = bin->labels_list;
	

	while(tmp)
	{
	
		tmpi = tmp->instruct;
		printf("label  name is: {%s} with %d bytes_above)\n", tmp->label_name, tmp->bytes_above);
		//printf(" label name is \"%s\" - ",  tmp->label_name);
		// if (tmp->prev)
		// 	printf("label<-prev \"%s\" -", tmp->prev->label_name);
		// else
		// 	printf("no prev\n");
		// if (tmp->next)
		// 	printf("label->next \"%s\" \n", tmp->next->label_name);
		// else
		// 	printf("no next\n");
		k = 0;

		while(tmpi)
		{
			k = 0;

			bin->champ_size_nbr += tmpi->c_len;
			printf("	=>instruction is: %s and it's size  %d\n", tmpi->name_c, tmpi->c_len);
			printf("		args: ");
			while(tmpi->a[k])
			{
				// if (ft_strstr(a[k]), "%:")
				// {

				// }
				tmpi->args[k][0] = tmpi->arg[k];
				tmpi->args[k][1] = find_arg_value(bin, tmpi->a[k], tmpi, tmp);

				printf("{%s} ", tmpi->a[k]);
				k++;
			}
			// tmpi->inst_nbr = k;
			printf("\n");
			tmpi = tmpi->next;
		}
		tmp = tmp->next;
	}
	printf("executable code length: %x\n", bin->champ_size_nbr);
	//fill_arguments_array(bin);

}

