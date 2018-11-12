#include "asm.h"

void	ft_print_flag_a(t_binfile *bin)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", bin->file_length);
	ft_printf("Name : \"%s\"\n", bin->name);
	ft_printf("Comment : \"%s\"\n\n", bin->comment);

	
}

void	 		flag_a_output(t_binfile *bin)
{
	t_lable 	*lable;
	t_t			*instruct;
	int 		byte_nr;

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

			ft_printf("%-4d (%-3d) :%8s%-10s ", byte_nr, instruct->c_len, " ", instruct->name_c);
			byte_nr = byte_nr + instruct->c_len;
			print_arg_chars(instruct);


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
