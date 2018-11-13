#include "asm.h"

void 			ft_print_success(t_binfile *bin)
{
	int 		len;


	len = ft_strlen(bin->arg_name);
	printf("Writing output program to %s\n", bin->res_arg_name);

}

void			ft_print_usage()
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("%117s\n", "-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
	ft_printf("%117s\n", "-d : Compiles all files in the given directory");
	ft_printf("%117s\n", "-D : Compiles all files in the given directory and its subdirectories");
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

int 		colomn_definer(t_t *token, char *arg)
{
	char	*str;
	int 	i = 0;
	int  	l = 0;

	str = token->line_copy;
	while (str[i])
	{
		if (str[i] == arg[l])
		{
			l++;
			if (arg[l + 1] == '\0')
				return (i - l);
		}
		if (str[i] != arg[l - 1])
			l = 0;
		i++;
	}
	return (i - l);
}

int			error_message_label(t_t *token, char *label, char *arg)
{
	int 	colomn = colomn_definer(token, arg) + 1;

	printf("No such label %s while attempting to dereference token [TOKEN][%d:%d] %s {%s}\n",  label, token->line_num, colomn, "DIRECT_LABEL", arg);
	return (0);
}

int 		error_command(t_t *token, char *str)
{
	int 	colomn = colomn_definer(token, str);

	printf("Invalid instruction at token [TOKEN][%d:%d] INSTRUCTION {%s}\n", token->line_num + 2, colomn, str );
	return (0);
}

int			error_message(t_t *token, char *arg)
 {
 	char 	*e;
 	int 	colomn = colomn_definer(token, arg) + 1;

 	if (ft_strchr(arg ,'r') && !(ft_strchr(arg ,'%')))
 		e = ft_strdup("REGISTER");
 	else if (ft_strstr(arg, "%:"))
 		e = ft_strdup("DIRECT_LABEL");
 	else if (ft_strchr(arg ,'%'))
 		e = ft_strdup("DIRECT");
 	else if (ft_atoi(arg) != 0)
 		e = ft_strdup("INDIRECT");
 	else if (ft_strchr(arg , SEPARATOR_CHAR))
 		e = ft_strdup("SEPARATOR");
 	else if (ft_strchr(arg, ':'))
 		e = ft_strdup("LABEL");
 	else
 		e = ft_strdup("INSTRUCTION");
 	printf("Syntax error at token [TOKEN][%d:%d] %s {%s}\n",  token->line_num, colomn, e, arg);
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


//  .name "zork"
// .comment "I'M ALIIIIVE"

// l2:		sti r, %:live, %1
// 		and r1, %0, r1

// live:	live %1
// 		zjmp %:live

 