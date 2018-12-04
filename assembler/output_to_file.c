/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:41:56 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 15:41:58 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					print_exec_to_file(t_binfile *bin, size_t i)
{
	t_lable				*lable;
	t_t					*tmp;

	lable = bin->labels_list;
	while (lable)
	{
		tmp = lable->instruct;
		print_inst_file(tmp, i, bin);
		lable = lable->next;
	}
}

void					output_basics(t_binfile *bin)
{
	size_t				i;

	i = 0;
	while (i < 4)
	{
		write(bin->fd_file_out, &bin->magic_start[i], 1);
		i++;
	}
	i = 0;
	while (i < PROG_NAME_L)
	{
		write(bin->fd_file_out, &bin->name[i], 1);
		i++;
	}
	write(bin->fd_file_out, "\0\0\0\0", 4);
}

void					fill_corfile_contents(t_binfile *bin)
{
	size_t				i;
	t_lable				*lable;

	lable = bin->labels_list;
	output_basics(bin);
	print_four_bytes(bin->file_length, bin->fd_file_out);
	i = 0;
	while (i < COMMENT_L)
	{
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;
	}
	write(bin->fd_file_out, "\0\0\0\0", 4);
	print_exec_to_file(bin, 0);
	ft_print_success(bin);
}
