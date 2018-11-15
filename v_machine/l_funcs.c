/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_funcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:33:09 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/15 17:34:31 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	t_proc *tmp;
	t_proc *child_proc;

	tmp = head_proc;
	child_proc = NULL;
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	(*tmp).if_live = 1;
	(*tmp).last_live_cycle = (*main_cycle).cycles;
	(*tmp).lives++;
	(*tmp).live_cycle = 0;
	child_proc = tmp;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | live %d\n", (*tmp).id + 1, (*tmp).argv[0][1]);
	if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] <= 0)
	{
		(*child_proc).argv[0][1] = ((*child_proc).argv[0][1] * -1) - 1;
		if ((*child_proc).argv[0][1] <= (*head_proc).id)
		{
			tmp = head_proc;
			while (tmp && (*tmp).id != (*child_proc).argv[0][1])
				tmp = tmp->next;
			if (tmp)
			{
				(*tmp).last_live_cycle = (*main_cycle).cycles;
				if (((*main_cycle).verbose & 1))
					//ft_printf("A process shows that player %s
					//(champion_name) is alive.\n", (*tmp).name);
					ft_printf("Player %d (%s) is said to be alive\n",
					(*child_proc).argv[0][1] + 1, (*tmp).name);
			}
		}
	}
	map[0] = map[0];
	return (1);
}

void	take_ldi_params(t_instr *inst_vars, unsigned char *map)
{
	if (inst_vars->tmp->argv[0][0] == REG_CODE)
		(*inst_vars).one = inst_vars->tmp->regs[inst_vars->tmp->argv[0][1] - 1];
	else if (inst_vars->tmp->argv[0][0] == DIR_CODE)
		(*inst_vars).one = inst_vars->tmp->argv[0][1];
	else if (inst_vars->tmp->argv[0][0] == IND_CODE)
	{
		(*inst_vars).i = inst_vars->tmp->argv[0][1] % IDX_MOD +
		inst_vars->tmp->current_position;
		(*inst_vars).i = ((*inst_vars).i + MEM_SIZE) % MEM_SIZE;
		(*inst_vars).one = (map[(*inst_vars).i] << 24) + (map[((*inst_vars).i
		+ MEM_SIZE + 1) % MEM_SIZE] << 16) + (map[((*inst_vars).i + MEM_SIZE +
		2) % MEM_SIZE] << 8) + map[((*inst_vars).i + MEM_SIZE + 3) % MEM_SIZE];
	}
	if (inst_vars->tmp->argv[1][0] == REG_CODE)
		(*inst_vars).two = inst_vars->tmp->regs[inst_vars->tmp->argv[1][1] - 1];
	else if (inst_vars->tmp->argv[1][0] == DIR_CODE)
		(*inst_vars).two = inst_vars->tmp->argv[1][1];
	else if (inst_vars->tmp->argv[1][0] == IND_CODE)
	{
		(*inst_vars).i = inst_vars->tmp->argv[1][1] % IDX_MOD +
		inst_vars->tmp->current_position;
		(*inst_vars).i = ((*inst_vars).i + MEM_SIZE) % MEM_SIZE;
		(*inst_vars).two = (map[(*inst_vars).i] << 24) + (map[((*inst_vars).i +
		MEM_SIZE + 1) % MEM_SIZE] << 16) + (map[((*inst_vars).i + MEM_SIZE + 2)
		% MEM_SIZE] << 8) + map[((*inst_vars).i + MEM_SIZE + 3) % MEM_SIZE];
	}
}

int		load_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (!check_ldi_params(inst_vars))
		return (0);
	take_ldi_params(&inst_vars, map);
	inst_vars.i = (inst_vars.one + inst_vars.two) +
	inst_vars.tmp->current_position;
	if (((*main_cycle).verbose >> 2) & 1)
	{
		ft_printf("P%5d | ldi %d %d r%d\n", cur_proc + 1, inst_vars.one,
		inst_vars.two, inst_vars.tmp->argv[2][1]);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		inst_vars.one, inst_vars.two, inst_vars.one + inst_vars.two,
		inst_vars.i);
	}
	inst_vars.i = (inst_vars.i + MEM_SIZE) % MEM_SIZE;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] = (map[inst_vars.i]
	<< 24) + (map[(inst_vars.i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
	(map[(inst_vars.i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(inst_vars.i +
	MEM_SIZE + 3) % MEM_SIZE];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int		lload(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[1][0] != REG_CODE || inst_vars.tmp->argv[1][1] < 1
		|| inst_vars.tmp->argv[1][1] > 16 || inst_vars.tmp->argv[2][0])
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
	{
		inst_vars.i = inst_vars.tmp->current_position +
		inst_vars.tmp->argv[0][1];
		inst_vars.i = (inst_vars.i + MEM_SIZE) % MEM_SIZE;
		if (((map[inst_vars.i] << 24) + (map[(inst_vars.i + MEM_SIZE + 1) %
		MEM_SIZE] << 16) + (map[(inst_vars.i + MEM_SIZE + 2) % MEM_SIZE] << 8)
		+ map[(inst_vars.i + MEM_SIZE + 3) % MEM_SIZE]) == 0)
			inst_vars.tmp->carry = 1;
		inst_vars.tmp->regs[inst_vars.tmp->argv[1][1] - 1] =
		(map[inst_vars.i] << 24) + (map[(inst_vars.i + MEM_SIZE + 1) %
		MEM_SIZE] << 16) + (map[(inst_vars.i + MEM_SIZE + 2) % MEM_SIZE] << 8)
		+ map[(inst_vars.i + MEM_SIZE + 3) % MEM_SIZE];
	}
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | lld %d r%d\n", cur_proc + 1,
		inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int check_ldi_params(t_instr inst_vars)
{
	if (inst_vars.tmp->argv[2][0] != REG_CODE || inst_vars.tmp->argv[2][1] < 1
	|| inst_vars.tmp->argv[2][1] > 16 || (inst_vars.tmp->argv[0][0] == REG_CODE
	&& (inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] > 16)) ||
	(inst_vars.tmp->argv[1][0] == REG_CODE && (inst_vars.tmp->argv[1][1] < 1 ||
	inst_vars.tmp->argv[1][1] > 16)) || (inst_vars.tmp->argv[1][0] != REG_CODE
	&& inst_vars.tmp->argv[1][0] != DIR_CODE))
		return (0);
	else
		return (1);
}

int		lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (!check_ldi_params(inst_vars))
		return (0);
	inst_vars.tmp->carry = 0;
	take_ldi_params(&inst_vars, map);
	inst_vars.i = (inst_vars.one + inst_vars.two) +
	inst_vars.tmp->current_position;
	if (((*main_cycle).verbose >> 2) & 1)
	{
		ft_printf("P%5d | lldi %d %d r%d\n", cur_proc + 1,
		inst_vars.tmp->argv[0][1],
		inst_vars.tmp->argv[1][1], inst_vars.tmp->argv[2][1]);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		inst_vars.one, inst_vars.two, inst_vars.one + inst_vars.two,
		inst_vars.i);
	}
	inst_vars.i = (inst_vars.i + MEM_SIZE) % MEM_SIZE;
	if (((map[inst_vars.i] << 24) + (map[(inst_vars.i + MEM_SIZE + 1) %
	MEM_SIZE] << 16) + (map[(inst_vars.i + MEM_SIZE + 2) % MEM_SIZE] <<
	8) + map[(inst_vars.i + MEM_SIZE + 3) % MEM_SIZE]) == 0)
		inst_vars.tmp->carry = 1;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] = (map[inst_vars.i] <<
	24) + (map[(inst_vars.i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
	(map[(inst_vars.i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(inst_vars.i +
	MEM_SIZE + 3) % MEM_SIZE];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}
