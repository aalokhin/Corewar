/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:32:45 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 15:54:25 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	lload_ind_parse(t_proc *tmp, unsigned char *map, int i)
{
	i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
	i = (i + MEM_SIZE) % MEM_SIZE;
	(*tmp).argv[0][1] = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) %
	MEM_SIZE] << 16) + (map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) +
	map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	if ((*tmp).argv[0][1] == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
}

int		load(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] ||
		((*tmp).argv[0][0] != DIR_CODE && (*tmp).argv[0][0] != IND_CODE))
		return (0);
	else if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 ||
		(*tmp).argv[1][1] > 16))
		return (1);
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == DIR_CODE)
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
		lload_ind_parse(tmp, map, i);
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
		(*tmp).argv[1][1]);
	return (1);
}

int		lload(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[1][0] != REG_CODE || inst_vars.tmp->argv[1][1] < 1
		|| inst_vars.tmp->argv[1][1] > 16 || inst_vars.tmp->argv[2][0] ||
		(inst_vars.tmp->argv[0][0] != DIR_CODE && inst_vars.tmp->argv[0][0]
		!= IND_CODE))
		return (0);
	inst_vars.tmp->carry = 0;
	if (inst_vars.tmp->argv[0][0] == DIR_CODE)
	{
		if (inst_vars.tmp->argv[0][1] == 0)
			inst_vars.tmp->carry = 1;
		inst_vars.tmp->regs[inst_vars.tmp->argv[1][1] - 1] =
		inst_vars.tmp->argv[0][1];
	}
	else if (inst_vars.tmp->argv[0][0] == IND_CODE)
		lload_ind_parse(inst_vars.tmp, map, inst_vars.i);
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | lld %d r%d\n", cur_proc + 1,
		inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
	return (1);
}
