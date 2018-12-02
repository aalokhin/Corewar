/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:43 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/14 14:56:48 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void get_args_value(int arg_size, unsigned int *dest, unsigned char *map, int *id_counter)
{
	int j;
	int k;

	j = 1;
	k = arg_size;
	while (j <= arg_size)
	{
		if (((k - 1) * 8) > 0)
			*dest += (map[((*id_counter) + j) % MEM_SIZE] << (k - 1) * 8);
		else
			*dest += map[((*id_counter) + j) % MEM_SIZE];
		k--;
		j++;
	}
}

void	get_t_dir_value(t_proc *processes, unsigned char *map,
	int arg_ind, int *id_counter)
{
	unsigned int	tmp_4;

	tmp_4 = 0;
	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		if (!g_op_tab[(int)(*processes).cmd - 1].label)
		{
			get_args_value(DIR_SIZE, &tmp_4, map, id_counter);
			(*processes).argv[arg_ind][1] = (unsigned int)tmp_4;
			(*id_counter) += DIR_SIZE;
		}
		else
		{
			get_args_value(DIR_SIZE / 2, &tmp_4, map, id_counter);
			(*processes).argv[arg_ind][1] = (short)tmp_4;
			(*id_counter) = (*id_counter) + DIR_SIZE / 2;
		}
	}
	(*processes).arg_counter++;
}

void	get_t_ind_value(t_proc *processes, unsigned char *map, int arg_ind,
	int *id_counter)
{
	short tmp;
	int j;
	int k;

	tmp = 0;
	j = 1;
	k = IND_SIZE;
	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		while (j <= IND_SIZE)
		{
			if (((k - 1) * 8) > 0)
				tmp += (short)(map[((*id_counter) + j) % MEM_SIZE] << (k - 1) * 8);
			else
				tmp += (short)map[((*id_counter) + j) % MEM_SIZE];
			k--;
			j++;
		}
		tmp = (short)tmp;
		(*processes).argv[arg_ind][1] = tmp;
		(*id_counter) += IND_SIZE;
	}
	(*processes).arg_counter++;
}

void	get_t_reg_value(t_proc *processes, unsigned char *map, int arg_ind,
	int *id_counter)
{
	unsigned char tmp;
	int j;
	int k;

	tmp = 0;
	j = 1;
	k = T_REG;
	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		while (j <= T_REG)
		{
			if (((k - 1) * 8) > 0)
				tmp += (unsigned char)(map[((*id_counter) + j) % MEM_SIZE] << (k - 1) * 8);
			else
				tmp += (unsigned char)map[((*id_counter) + j) % MEM_SIZE];
			k--;
			j++;
		}
		(*processes).argv[arg_ind][1] = (unsigned char)tmp;
		(*id_counter) += T_REG;
	}
	(*processes).arg_counter++;
}

void	get_args_values(t_proc *processes, unsigned char *map, int *id_counter)
{
	if ((*processes).argv[0][0])
		g_get_arg_vals[(*processes).argv[0][0] - 1](processes, map, 0,
			id_counter);
	if ((*processes).argv[1][0])
		g_get_arg_vals[(*processes).argv[1][0] - 1](processes, map, 1,
			id_counter);
	if ((*processes).argv[2][0])
		g_get_arg_vals[(*processes).argv[2][0] - 1](processes, map, 2,
			id_counter);
}

void	take_args(unsigned char codage, t_proc *processes)
{
	if ((codage & 192) == 64)
		(*processes).argv[0][0] = REG_CODE;
	else if ((codage & 192) == 192)
		(*processes).argv[0][0] = IND_CODE;
	else if ((codage & 192) == 128)
		(*processes).argv[0][0] = DIR_CODE;
	if ((codage & 48) == 32)
		(*processes).argv[1][0] = DIR_CODE;
	else if ((codage & 48) == 48)
		(*processes).argv[1][0] = IND_CODE;
	else if ((codage & 48) == 16)
		(*processes).argv[1][0] = REG_CODE;
	if ((codage & 12) == 8)
		(*processes).argv[2][0] = DIR_CODE;
	else if ((codage & 12) == 12)
		(*processes).argv[2][0] = IND_CODE;
	else if ((codage & 12) == 4)
		(*processes).argv[2][0] = REG_CODE;
}
