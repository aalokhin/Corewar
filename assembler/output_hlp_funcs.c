/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_hlp_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:09:43 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 16:09:44 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					print_four_bytes(unsigned int src, int fd_out)
{
	unsigned char		a[4];
	int					i;

	i = 0;
	a[3] = src & 255;
	a[2] = (src >> 8) & 255;
	a[1] = (src >> 16) & 255;
	a[0] = (src >> 24) & 255;
	while (i < 4)
	{
		write(fd_out, &a[i], 1);
		i++;
	}
}

void					print_reg_to_file(int i, t_t *tmp, int fd_out)
{
	unsigned char		a;

	a = tmp->args[i][1] & 0xFF;
	write(fd_out, &a, 1);
}

void					print_ind_to_file(int i, t_t *tmp, int fd_out)
{
	unsigned char		a[2];
	int					z;

	a[1] = tmp->args[i][1] & 0xFF;
	a[0] = (tmp->args[i][1] >> 8) & 0xFF;
	z = 0;
	while (z < 2)
	{
		write(fd_out, &a[z], 1);
		z++;
	}
}

void					print_dir_to_file(int i, t_t *tmp, int fd_out)
{
	if (tmp->lbl_size == 4)
		print_four_bytes((unsigned int)tmp->args[i][1], fd_out);
	else
		print_ind_to_file(i, tmp, fd_out);
}

void					print_inst_file(t_t *tmp, size_t i, t_binfile *bin)
{
	unsigned char		a[4];

	i = 0;
	while (tmp)
	{
		a[0] = tmp->opcode & 0xFF;
		write(bin->fd_file_out, &a, 1);
		if (tmp->has_codage)
		{
			a[0] = tmp->codage & 0xFF;
			write(bin->fd_file_out, &a, 1);
		}
		i = 0;
		while (i < (size_t)tmp->arguments)
		{
			if (tmp->args[i][0] == 10)
				print_dir_to_file(i, tmp, bin->fd_file_out);
			else if (tmp->args[i][0] == 11)
				print_ind_to_file(i, tmp, bin->fd_file_out);
			else if (tmp->args[i][0] == 1)
				print_reg_to_file(i, tmp, bin->fd_file_out);
			i++;
		}
		tmp = tmp->next;
	}
}
