#include "asm.h"

void			ft_print_usage()
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("%117s\n", "-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
}

void 			ft_print_inv_f(char *s_file)
{
	ft_printf("Source file error ====>[%s]<=== \n", s_file);

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


int			error_message_label(char *label, char *arg)
 {
 	printf("No such label %s while attempting to dereference token [TOKEN][%d:%d] %s {%s}\n",  label, 0, 0, "DIRECT_LABEL", arg);
 	return (0);
 }

 int			error_message(char *arg)
 {
 	char 	*e;
 	int 	type;

 	type = (ft_strchr(arg ,'r') && !(ft_strchr(arg ,'%'))) ? 1 : ft_strchr(arg ,'%') ? 2 : ft_strchr(arg , SEPARATOR_CHAR) ? 5 : ft_atoi(arg) != 0 ? 4 : 0;
 	if (type == 1)
 		e = ft_strdup("REGISTER");
 	else if (type == 2)
 		e = ft_strdup("DIRECT");
 	else if (type == 4)
 		e = ft_strdup("INDIRECT");
 	else if (type == 5)
 		e = ft_strdup("SEPARATOR");
 	else
 		e = ft_strdup("INSTRUCTION");
 	printf("Syntax error at token [TOKEN][%d:%d] %s {%s}\n", 0, 0, e, arg);
 	//printf("%s\n", w_str);

 	return (0);
 }

 int 		error_invalid_arg_type(t_t *command, int arg, int size)
 {
 	char 	*type;

 	if (size == 1)
 		type = ft_strdup("register");
 	else if (size == 2)
 		type = ft_strdup("direct");
 	else
 		type = ft_strdup("indirect");
 	ft_printf("Invalid parameter %d type %s for instruction %s\n", arg, type, command->name_c);
 	return (0);
 }
 