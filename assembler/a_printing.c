#include "asm.h"

void				print_arg_chars(t_t *instruct) //костыль для двоеточия
{
	size_t			i;
	uintmax_t		len;

	len = 0;
	i = 0;
	while (instruct->a[i])
	{
		if (instruct->a[i])
		{
			len = ft_strlen(instruct->a[i]);
			if (len && instruct->a[i][len - 1] == ':')
				instruct->a[i][len - 1] = '\0';
			i++;
		}
	}
	i = 0;
	while (instruct->a[i])
	{
		ft_printf("%-18s", instruct->a[i]);
		i++;
	}
}

void				print_dir_ind_bytes(int arg, int lbl_size)
{
	unsigned char	a[4];
	int				k;

	k = -1;
	if (lbl_size == 4)
	{
		a[3] = arg & 0x000000FF;
		a[2] = (arg & 0x0000FF00) >> 8;
		a[1] = (arg & 0x00FF0000) >> 16;
		a[0] = (arg & 0xFF000000) >> 24;
		while (++k < 4)
			ft_printf("%-4d", a[k]);
	}
	else if (lbl_size == 2)
	{
		a[1] = arg & 0xFF;
		a[0] = (arg >> 8) & 0xFF;
		while (++k < 2)
			ft_printf("%-4d", a[k]);
	}
}

void				print_instr_args(t_t *instruct)
{
	size_t			i;

	i = 0;
	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);
	while (instruct->args[i][0])
	{
		if (instruct->args[i][0] == 1)
			ft_printf("%-18d", instruct->args[i][1]);
		else if (instruct->args[i][0] == 10 || instruct->args[i][0] == 11)
		{
			if (instruct->a[i][0] != ':' && instruct->a[i][1] != ':')
				print_dir_ind_bytes(instruct->args[i][1], instruct->lbl_size);
			else
				print_dir_ind_bytes(instruct->args[i][1], instruct->lbl_size);
			if (instruct->lbl_size == 2)
				ft_printf("%10s", " ");
			else
				ft_printf("%2s", " ");
		}
		i++;
	}
	print_instr_args2(instruct);
}

void				print_instr_args2(t_t *instruct)
{
	size_t			i;

	i = 0;
	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);
	while (instruct->args[i][0])
	{
		if (instruct->args[i][0] == 1)
		{
			ft_printf("%-18d", instruct->args[i][1]);
		}
		else if (instruct->args[i][0] == 10 || instruct->args[i][0] == 11)
		{
			if (instruct->a[i][0] != '%' && instruct->a[i][0] != ':'\
			&& instruct->a[i][0] != 'r')
				ft_printf("%-18s", instruct->a[i]);
			else
				ft_printf("%-18d", instruct->args[i][1]);
		}
		i++;
	}
}
