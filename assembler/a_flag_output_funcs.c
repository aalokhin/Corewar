#include "asm.h"

void	ft_print_flag_a(t_binfile *bin)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", bin->file_length);
	ft_printf("Name : \"%s\"\n", bin->name);
	ft_printf("Comment : \"%s\"\n\n", bin->comment);

	
}

void		print_instr_args(t_t *instruct)
{
	size_t i;
	unsigned 	tmp[4];
	int z;


	z = 0;

	i = 0;
	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);


	while (instruct->args[i][0])
	{
		z = 0;
		
		if (instruct->args[i][0] == 1)
		{	
			instruct->a[i]++;
			ft_printf("%s ", instruct->a[i]);
		}
		else if (instruct->args[i][0] == 10) //is directory
		{
			if (instruct->lbl_size == 4)
			{
				tmp[3] = instruct->args[i][1] & 0x000000FF;
				tmp[2] = (instruct->args[i][1] & 0x0000FF00) >> 8;
				tmp[1] = (instruct->args[i][1] & 0x00FF0000) >> 16;
				tmp[0    ] = (instruct->args[i][1] & 0xFF000000) >> 24;
				z =  0;
				while(z < 4)
				{
					printf("%d ", tmp[z]);
					//write(bin->fd_file_out, &a[z], 1);
					z++;
				}
			}
			else // == 2
			{
				tmp[1] = instruct->args[i][1] & 0xFF;
				tmp[0] = (instruct->args[i][1] >> 8) & 0xFF;
				z =  0;
				while(z < 2)
				{
					printf("%d ", tmp[z]);
					z++;
				}
			}
		
			// if (instruct->has_codage)
			// 	ft_printf("%-18d", instruct->args[i][1]);
		}
		i++;
	}
	
}

void	 		flag_a_output(t_binfile *bin)
{
	t_lable 	*lable;
	t_t			*instruct;
	int 		byte_nr;
	int 		i;
	//char		tmp[4];

	byte_nr = 0;
	lable = bin->labels_list;
	instruct = lable->instruct;
	while (lable)
	{
		if (lable->label_name)
			(lable->instruct) ? ft_printf("%-4d       :    %s\n", lable->bytes_above,  lable->label_name) : ft_printf("%-4d       :    %s\n", byte_nr, lable->label_name);
		instruct = lable->instruct;
		while(instruct)
		{
			i = 0;
			ft_printf("%-4d (%-3d) :%8s%-10s ", byte_nr, instruct->c_len, " ", instruct->name_c);
			byte_nr = byte_nr + instruct->c_len;
			while (instruct->a[i])
			{
				ft_printf("%-18s",  instruct->a[i]);
				i++;
			}
			print_instr_args(instruct);
			// i = 0;
			// while (instruct->args[i][0])
			// {
			// 	ft_printf("%-18d\n", tmp[i]);
			// 	i++;
			// }
			printf("\n\n");
			instruct = instruct->next;
		}
		lable = lable->next;
	}

}




// while (a)
// {
// 	a->name[0] == 'r' ? ft_reg(&a->name[1]) :
// 	ft_pr_di(a, 0, name);
// 	a = a->next;
// }
// (c == 2) ? ft_printf("\n%20s%-4d%-6d", " ", o, ft_ct(arg, NULL, 0)) :
// ft_printf("\n%20s%-10d", " ", o);
// a = arg;
// while (a)
// {
// 	(a->name[0] == 'r') ? ft_reg(&a->name[1]) :
// 	ft_pr_di(a, 1, name);
// 	a = a->next;
// }



// void	ft_reg(char *str)
// {
// 	if (str[0] == '0')
// 	{
// 		if (str[1] != '\0')
// 			ft_printf("%-18s", &str[1]);
// 		else
// 			ft_printf("%-18s", str);
// 	}
// 	else
// 		ft_printf("%-18s", str);
// }


// void	ft_pr_di(t_lb *a, int i, char *op)
// {
// 	if (i == 0)
// 	{
// 		if (a->name[0] != ':' && a->name[1] != ':')
// 			(a->name[0] == '%') ? ft_cod(ft_atoi(&a->name[1]), op, a->name) :
// 		ft_cod(ft_atoi(a->name), op, a->name);
// 		else
// 			ft_cod(a->len, op, a->name);
// 	}
// 	if (i == 1 && !(a->name[0] == '%' || a->name[0] == ':' ||
// 		a->name[0] == 'r'))
// 		ft_printf("%-18s", a->name);
// 	else if (i == 1 && (a->name[0] == '%' && a->name[1] != ':'))
// 		ft_printf("%-18d", ft_atoi(&a->name[1]));
// 	else if (i == 1)
// 		ft_printf("%-18d", a->len);
// }

