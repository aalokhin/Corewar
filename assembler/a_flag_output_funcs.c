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
			printf("\n\n");
			instruct = instruct->next;
		}
		lable = lable->next;
	}

}