/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_funcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:21:47 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/15 17:22:12 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	take_sti_params(t_instr *inst_vars, unsigned char *map)
{
	if (inst_vars->tmp->argv[1][0] == REG_CODE)
		(*inst_vars).one = inst_vars->tmp->regs[inst_vars->tmp->argv[1][1] - 1];
	else if (inst_vars->tmp->argv[1][0] == DIR_CODE)
		(*inst_vars).one = inst_vars->tmp->argv[1][1];
	else if (inst_vars->tmp->argv[1][0] == IND_CODE)
	{
		(*inst_vars).i = inst_vars->tmp->current_position +
		inst_vars->tmp->argv[1][1] % IDX_MOD;
		(*inst_vars).i = (((*inst_vars).i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
		(*inst_vars).one = (map[(*inst_vars).i % MEM_SIZE] << 24) +
		(map[((*inst_vars).i + 1) % MEM_SIZE] << 16) + (map[((*inst_vars).i + 2)
		% MEM_SIZE] << 8) + map[((*inst_vars).i + 3) % MEM_SIZE];
	}
	if (inst_vars->tmp->argv[2][0] == REG_CODE)
		(*inst_vars).two = inst_vars->tmp->regs[inst_vars->tmp->argv[2][1] - 1];
	else if (inst_vars->tmp->argv[2][0] == DIR_CODE)
		(*inst_vars).two = inst_vars->tmp->argv[2][1];
}

void	print_sti(t_cycle *main_cycle, int cur_proc, t_instr inst_vars)
{
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | sti r%d %d %d\n", cur_proc + 1,
			inst_vars.tmp->argv[0][1], inst_vars.one, inst_vars.two);
		else
			ft_printf("P%6d | sti r%d %d %d\n", cur_proc + 1,
			inst_vars.tmp->argv[0][1], inst_vars.one, inst_vars.two);
		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|',
		inst_vars.one, inst_vars.two, inst_vars.one +
		inst_vars.two, inst_vars.i);
	}
}

void	store_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[0][0] != REG_CODE || (inst_vars.tmp->argv[2][0]
	!= REG_CODE && inst_vars.tmp->argv[2][0] != DIR_CODE) ||
	inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] > REG_NUMBER
	|| (inst_vars.tmp->argv[1][0] == REG_CODE && (inst_vars.tmp->argv[1][1]
	< 1 || inst_vars.tmp->argv[1][1] > REG_NUMBER)) ||
	(inst_vars.tmp->argv[2][0] == REG_CODE && (inst_vars.tmp->argv[2][1]
	< 1 || inst_vars.tmp->argv[2][1] > REG_NUMBER)))
		return ;
	take_sti_params(&inst_vars, map);
	inst_vars.i = inst_vars.tmp->current_position +
	(inst_vars.one + inst_vars.two);
	if (inst_vars.i > 65535)
		inst_vars.i %= IDX_MOD;
	print_sti(main_cycle, cur_proc, inst_vars);
	inst_vars.i = ((inst_vars.i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
	insert_vals_to_map(map, inst_vars, main_cycle);
}

void	print_st(t_cycle *main_cycle, int cur_proc, t_instr inst_vars)
{
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | st r%d %d\n", cur_proc + 1,
			inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
		else
			ft_printf("P%6d | st r%d %d\n", cur_proc + 1,
			inst_vars.tmp->argv[0][1], inst_vars.tmp->argv[1][1]);
	}
}

void	store(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[0][0] != REG_CODE || (inst_vars.tmp->argv[1][0]
		!= REG_CODE && inst_vars.tmp->argv[1][0] != IND_CODE) ||
		inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] > REG_NUMBER)
		return ;
	if (inst_vars.tmp->argv[1][0] == IND_CODE)
	{
		inst_vars.i = (((inst_vars.tmp->current_position +
		inst_vars.tmp->argv[1][1] % IDX_MOD) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
		insert_vals_to_map(map, inst_vars, main_cycle);
	}
	else if (inst_vars.tmp->argv[1][0] == REG_CODE)
	{
		inst_vars.tmp->regs[inst_vars.tmp->argv[1][1] - 1] =
		inst_vars.tmp->regs[inst_vars.tmp->argv[0][1] - 1];
	}
	print_st(main_cycle, cur_proc, inst_vars);
}
