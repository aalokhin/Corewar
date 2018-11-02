#include "asm.h"

void			ft_print_usage()
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("%117s\n", "-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
}

void 			ft_print_inv_f()
{
	ft_printf("Source file error\n");

	// should be something like  ft_printf("Syntax error at token [TOKEN][001:001] END \"(null)\"");
}




void	ft_print_inv_input()
{
	ft_printf("Input error\n");
}

void	ft_print_flag_a(t_binfile *bin)
{
	ft_printf("Dumping annotated program on standard output\n");
	printf("Program size : %u bytes\n", bin->champ_size_nbr);
	printf("Name : %s \n", bin->name);
	printf("Comment : %s\n\n", bin->comment);

	
}


