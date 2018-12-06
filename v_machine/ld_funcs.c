/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:21:01 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/04 17:21:04 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	load(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc	*tmp;

	tmp = processes;
	if ((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[1][1] < 1 ||
		(*tmp).argv[1][1] > REG_NUMBER ||
		((*tmp).argv[0][0] != DIR_CODE && (*tmp).argv[0][0] != IND_CODE))
		return ;
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == DIR_CODE)
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
		lload_ind_parse(tmp, map, 0);
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
		(*tmp).argv[1][1]);
		else
			ft_printf("P%6d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
		(*tmp).argv[1][1]);
	}
}

void	print_lld(t_cycle *main_cycle, int cur_proc, t_instr inst_vars)
{
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | lld %d r%d\n", cur_proc + 1,
		inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
		else
			ft_printf("P%6d | lld %d r%d\n", cur_proc + 1,
		inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
	}
}

void	lload(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[1][0] != REG_CODE || (inst_vars.tmp->argv[0][0]
	!= DIR_CODE && inst_vars.tmp->argv[0][0] != IND_CODE) ||
	inst_vars.tmp->argv[1][1] < 1 || inst_vars.tmp->argv[1][1] > REG_NUMBER)
		return ;
	inst_vars.tmp->carry = 0;
	if (inst_vars.tmp->argv[0][0] == DIR_CODE)
	{
		if (inst_vars.tmp->argv[0][1] == 0)
			inst_vars.tmp->carry = 1;
		inst_vars.tmp->regs[inst_vars.tmp->argv[1][1] - 1] =
		inst_vars.tmp->argv[0][1];
	}
	else if (inst_vars.tmp->argv[0][0] == IND_CODE)
		lload_ind_parse(inst_vars.tmp, map, 1);
	print_lld(main_cycle, cur_proc, inst_vars);
}

void	load_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (!check_ldi_params(&inst_vars, map, 0))
		return ;
	inst_vars.i = (inst_vars.one + inst_vars.two) +
	inst_vars.tmp->current_position;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		print_ldi_instr(0, cur_proc, inst_vars);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		inst_vars.one, inst_vars.two, inst_vars.one + inst_vars.two,
		inst_vars.i);
	}
	inst_vars.i = ((inst_vars.i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] = (map[inst_vars.i
	% MEM_SIZE] << 24) + (map[(inst_vars.i + 1) %
	MEM_SIZE] << 16) + (map[(inst_vars.i + 2) % MEM_SIZE] << 8) +
	map[(inst_vars.i + 3) % MEM_SIZE];
}

void	lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (!check_ldi_params(&inst_vars, map, 1))
		return ;
	inst_vars.tmp->carry = 0;
	inst_vars.i = ((((inst_vars.one + inst_vars.two) +
		inst_vars.tmp->current_position) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		print_ldi_instr(1, cur_proc, inst_vars);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		inst_vars.one, inst_vars.two, inst_vars.one + inst_vars.two,
		(inst_vars.one + inst_vars.two) + inst_vars.tmp->current_position);
	}
	inst_vars.new_ind = (map[inst_vars.i % MEM_SIZE] << 24) +
	(map[(inst_vars.i + 1) % MEM_SIZE] << 16) +
	(map[(inst_vars.i + 2) % MEM_SIZE] << 8) +
	map[(inst_vars.i + 3) % MEM_SIZE];
	if (inst_vars.new_ind == 0)
		inst_vars.tmp->carry = 1;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] = inst_vars.new_ind;
}
