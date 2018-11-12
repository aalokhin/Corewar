#include "asm.h"

void		print_arg_chars(t_t			*instruct)
{
	int i;

	i = 0;
	while (instruct->a[i])
	{
		ft_printf("%-18s",  instruct->a[i]);
		i++;
	}
}

void		print_dir_ind_bytes(int arg, int lbl_size)
{
	unsigned char	a[4];
	int 			k;

	k = 0;
	if (lbl_size == 4)
	{
		a[3] = arg & 0x000000FF;
		a[2] = (arg & 0x0000FF00) >> 8;
		a[1] = (arg & 0x00FF0000) >> 16;
		a[0] = (arg & 0xFF000000) >> 24;
		while (k < 4)
		{
			ft_printf("%-3d ", a[k]);
			k++;
		}
		// ft_printf("%1s", " ");
		
	}
	else if (lbl_size == 2)
	{
		a[1] = arg & 0xFF;
		a[0] = (arg >> 8) & 0xFF;
		while (k < 2)
		{
			ft_printf("%-3d ", a[k]);
			k++;
		}
		// ft_printf("%10s", " ");
		///ft_printf("%4s", " ");
	}
	// if (lbl_size == 4)
	// 	ft_printf("%4s", " ");
	// else
		


}








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

// void	ft_pr_nums(char *name, t_lb *arg)
// {
// 	int		o;
// 	int		c;
// 	t_lb	*a;

// 	a = arg;
// 	o = ft_op_id(name, NULL, 0);
// 	c = ft_cotage(name);
// 	(c == 2) ? ft_printf("\n%20s%-4d%-6d", " ", o, ft_ct(arg, NULL, 0)) :
// 	ft_printf("\n%20s%-10d", " ", o);
// 	while (a)
// 	{
// 		a->name[0] == 'r' ? ft_reg(&a->name[1]) :
// 		ft_pr_di(a, 0, name);
// 		a = a->next;
// 	}
// 	(c == 2) ? ft_printf("\n%20s%-4d%-6d", " ", o, ft_ct(arg, NULL, 0)) :
// 	ft_printf("\n%20s%-10d", " ", o);
// 	a = arg;
// 	while (a)
// 	{
// 		(a->name[0] == 'r') ? ft_reg(&a->name[1]) :
// 		ft_pr_di(a, 1, name);
// 		a = a->next;
// 	}
// 	ft_printf("\n\n");
// }



// if (a->name[0] != ':' && a->name[1] != ':')
// 			(a->name[0] == '%') ? ft_cod(ft_atoi(&a->name[1]), op, a->name) :
// 		ft_cod(ft_atoi(a->name), op, a->name);
// 		else
// 			ft_cod(a->len, op, a->name);




void		print_instr_args(t_t *instruct)
{
	size_t i;

	i = 0;
	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);

	while (instruct->args[i][0])
	{

		// printf("arg: %d ", instruct->args[i][0]);
		// printf("val: %d", instruct->args[i][1]);
		
		if (instruct->args[i][0] == 1)
		{	

			ft_printf("%-19d", instruct->args[i][1]);
		}
		else if (instruct->args[i][0] == 10 || instruct->args[i][0] == 11) //is directory
		{
			if (instruct->a[i][0] != ':' && instruct->a[i][1] != ':')
			{
				// if (instruct->a[i][0] == '%')
					print_dir_ind_bytes(instruct->args[i][1], instruct->lbl_size);


			}
			else
			{
				print_dir_ind_bytes(instruct->args[i][1], instruct->lbl_size);

				 // ft_printf("%-4d%-4d", instruct->args[i][1] >> 24, (instruct->args[i][1] >> 16) & 255);
				 // ft_printf("%-4d%-4d", (instruct->args[i][1] >> 8) & 255, instruct->args[i][1] & 255);
				//ft_printf(">>>>>%-4d", instruct->args[i][1]);
			}

			(instruct->lbl_size == 2) ? ft_printf("%10s", " ") : ft_printf("%3s", " ");

			// if (instruct->has_codage)
			// 	ft_printf("%-18d", instruct->args[i][1]);
		}
		
		i++;
	}
	ft_printf("\n");

	i = 0;

	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);
	


	while (instruct->args[i][0])
	{
		
		if (instruct->args[i][0] == 1)
		{	
			ft_printf("%-19d", instruct->args[i][1]);
		}
		else if (instruct->args[i][0] == 10 || instruct->args[i][0] == 11) //is directory
		{
			//print_dir_ind_bytes(instruct->args[i][1], instruct->lbl_size);
			
			if (instruct->a[i][0] != '%' && instruct->a[i][0] != ':' && instruct->a[i][0] != 'r')
				ft_printf("%-18s", instruct->a[i]);
			else
				ft_printf("%-18d", instruct->args[i][1]);


			(instruct->lbl_size == 2) ? ft_printf("%8s", " ") : ft_printf("%2s", " ");

		}
		
		i++;
	}
	
}
	


// if (i == 1 && !(a->name[0] == '%' || a->name[0] == ':' ||
// 	a->name[0] == 'r'))
// 	ft_printf("%-18s", a->name);
// else if (i == 1 && (a->name[0] == '%' && a->name[1] != ':'))
// 	ft_printf("%-18d", ft_atoi(&a->name[1]));
// else if (i == 1)
// 	ft_printf("%-18d", a->len);