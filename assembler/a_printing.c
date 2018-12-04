/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_printing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:18:16 by aalokhin          #+#    #+#             */
/*   Updated: 2018/11/30 16:18:25 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				print_arg_chars(t_t *instruct)
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
			if (len && instruct->a[i][len - 1] == LABEL_CHAR)
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

void				ind_dir_print(int arg0, int arg, int lbl_size)
{
	unsigned char	a[4];
	int				k;

	k = -1;
	if (lbl_size == 4 && arg0 != 11)
	{
		a[3] = arg & 0x000000FF;
		a[2] = (arg & 0x0000FF00) >> 8;
		a[1] = (arg & 0x00FF0000) >> 16;
		a[0] = (arg & 0xFF000000) >> 24;
		while (++k < 4)
			ft_printf("%-4d", a[k]);
	}
	else if (lbl_size == 2 || arg0 == 11)
	{
		a[1] = arg & 0xFF;
		a[0] = (arg >> 8) & 0xFF;
		while (++k < 2)
			ft_printf("%-4d", a[k]);
	}
}

void				print_opcode(t_t *instruct)
{
	if (instruct->has_codage)
		ft_printf("\n%20s%-4d%-6d", " ", instruct->opcode, instruct->codage);
	else
		ft_printf("\n%20s%-10d", " ", instruct->opcode);
}

void				print_instr_args(t_t *ins)
{
	size_t			i;

	i = 0;
	print_opcode(ins);
	while (ins->args[i][0])
	{
		if (!ins->a[i])
			break ;
		if (ins->args[i][0] == 1)
			ft_printf("%-18d", ins->args[i][1]);
		else if (ins->args[i][0] == 10 || ins->args[i][0] == 11)
		{
			if (ins->a[i][0] != LABEL_CHAR && ins->a[i][1] != LABEL_CHAR)
				ind_dir_print(ins->args[i][0], ins->args[i][1], ins->lbl_size);
			else
				ind_dir_print(ins->args[i][0], ins->args[i][1], ins->lbl_size);
			if (ins->lbl_size == 2 || ins->args[i][0] == 11)
				ft_printf("%10s", " ");
			else
				ft_printf("%2s", " ");
		}
		i++;
	}
	print_instr_args2(ins);
}

void				print_instr_args2(t_t *instruct)
{
	size_t			i;

	i = 0;
	print_opcode(instruct);
	while (instruct->args[i][0])
	{
		if (!instruct->a[i])
			break ;
		if (instruct->args[i][0] == 1)
		{
			ft_printf("%-18d", instruct->args[i][1]);
		}
		else if (instruct->args[i][0] == 10 || instruct->args[i][0] == 11)
		{
			if (instruct->a[i][0] != DIRECT_CHAR && instruct->a[i][0] != LABEL_CHAR\
			&& instruct->a[i][0] != 'r')
				ft_printf("%-18s", instruct->a[i]);
			else
				ft_printf("%-18d", instruct->args[i][1]);
		}
		i++;
	}
}
