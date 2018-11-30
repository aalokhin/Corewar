/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_flag_output_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:08:15 by aalokhin          #+#    #+#             */
/*   Updated: 2018/11/30 16:08:17 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_print_flag_a(t_binfile *bin)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", bin->file_length);
	ft_printf("Name : \"%s\"\n", bin->name);
	ft_printf("Comment : \"%s\"\n\n", bin->comment);
}

void			print_instructions(int *byte_nr, t_t *lbl_instr)
{
	t_t			*instruct;

	instruct = lbl_instr;
	while (instruct)
	{
		ft_printf("%-4d (%-3d) :", *byte_nr, instruct->c_len);
		ft_printf("%8s%-10s", " ", instruct->name_c);
		*byte_nr += instruct->c_len;
		print_arg_chars(instruct);
		print_instr_args(instruct);
		ft_printf("\n\n");
		instruct = instruct->next;
	}
}

void			flag_a_output(t_binfile *bin)
{
	t_lable		*lable;
	int			byte_nr;

	byte_nr = 0;
	lable = bin->labels_list;
	while (lable)
	{
		if (lable->label_name)
		{
			if (lable->instruct)
				ft_printf("%-4d%-7s:", lable->bytes_above, " ");
			else
				ft_printf("%-4d%-7s:", byte_nr, " ");
			ft_printf("%-4s%s\n", " ", lable->label_name);
		}
		print_instructions(&byte_nr, lable->instruct);
		lable = lable->next;
	}
}
