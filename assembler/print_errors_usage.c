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



// void	(int num, char *name, char *com)
// {
// 	write(1, "Dumping annotated program on standard output\n", 45);
// 	write(1, "Program size : ", 15);
// 	ft_putnbr(num);
// 	write(1, " bytes\nName : \"", 15);
// 	write(1, name, ft_strlen(name));
// 	write(1, "\"\nComment : \"", 13);
// 	write(1, com, ft_strlen(com));
// 	write(1, "\"\n\n", 3);
// }