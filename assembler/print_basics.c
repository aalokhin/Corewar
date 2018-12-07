/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:39:14 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 16:39:16 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_print_success(t_binfile *bin)
{
	int			len;

	len = ft_strlen(bin->arg_name);
	ft_printf("Writing output program to %s\n", bin->res_arg_name);
}

void			ft_print_usage(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("%-117s\n",\
	"-a : Instead of creating a .cor file, outputs a stripped and \
annotated version of the code to the standard output");
	ft_printf("%-117s\n",\
	"-d : Compiles all files in the given directory");
	ft_printf("%-117s\n",\
	"-D : Compiles all files in the given directory and its subdirectories");
}

void			ft_print_inv_f(char *s_file)
{
	ft_printf("Source file error ====>[%s]<=== \n", s_file);
}

void			ft_print_inv_input(void)
{
	ft_printf("Input error\n");
}
