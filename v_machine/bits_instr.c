/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:47:12 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/15 18:47:36 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	take_bits_params(t_instr *inst_vars, unsigned char *map)
{
	if (inst_vars->tmp->argv[0][0] == REG_CODE)
		(*inst_vars).one = inst_vars->tmp->regs[inst_vars->tmp->argv[0][1] - 1];
	else if (inst_vars->tmp->argv[0][0] == DIR_CODE)
		(*inst_vars).one = inst_vars->tmp->argv[0][1];
	else if (inst_vars->tmp->argv[0][0] == IND_CODE)
	{
		(*inst_vars).i = inst_vars->tmp->current_position +
		inst_vars->tmp->argv[0][1] % IDX_MOD;
		(*inst_vars).i = (((*inst_vars).i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
		(*inst_vars).one = ((map[(*inst_vars).i % MEM_SIZE] << 24) + (map[((*inst_vars).i
		+ 1) % MEM_SIZE] << 16) + (map[((*inst_vars).i + 
		2) % MEM_SIZE] << 8) + map[((*inst_vars).i + 3) % MEM_SIZE]);
	}
	if (inst_vars->tmp->argv[1][0] == REG_CODE)
		(*inst_vars).two = inst_vars->tmp->regs[inst_vars->tmp->argv[1][1] - 1];
	else if (inst_vars->tmp->argv[1][0] == DIR_CODE)
		(*inst_vars).two = inst_vars->tmp->argv[1][1];
	else if (inst_vars->tmp->argv[1][0] == IND_CODE)
	{
		(*inst_vars).i = (((inst_vars->tmp->current_position +
		inst_vars->tmp->argv[1][1] % IDX_MOD) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
		(*inst_vars).two = ((map[(*inst_vars).i % MEM_SIZE] << 24) + (map[((*inst_vars).i +
		1) % MEM_SIZE] << 16) + (map[((*inst_vars).i + 2)
		% MEM_SIZE] << 8) + map[((*inst_vars).i + 3) % MEM_SIZE]);
	}
}

void	bit_and(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[2][0] != REG_CODE || inst_vars.tmp->argv[2][1] < 1
	|| inst_vars.tmp->argv[2][1] > REG_NUMBER || (inst_vars.tmp->argv[0][0] ==
	REG_CODE && (inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] >
	REG_NUMBER)) || (inst_vars.tmp->argv[1][0] == REG_CODE &&
	(inst_vars.tmp->argv[1][1] < 1 || inst_vars.tmp->argv[1][1] > REG_NUMBER)))
		return ;
	take_bits_params(&inst_vars, map);
	inst_vars.tmp->carry = 0;
	if ((inst_vars.one & inst_vars.two) == 0)
		inst_vars.tmp->carry = 1;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] =
	inst_vars.one & inst_vars.two;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			printf("P%5d | and %d %d r%d\n", cur_proc + 1, inst_vars.one,
			inst_vars.two, inst_vars.tmp->argv[2][1]);
		else
			printf("P%6d | and %d %d r%d\n", cur_proc + 1, inst_vars.one,
			inst_vars.two, inst_vars.tmp->argv[2][1]);
	}
}

void	bit_or(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[2][0] != REG_CODE || inst_vars.tmp->argv[2][1] < 1
	|| inst_vars.tmp->argv[2][1] > REG_NUMBER || (inst_vars.tmp->argv[0][0] ==
	REG_CODE && (inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] >
	REG_NUMBER)) || (inst_vars.tmp->argv[1][0] == REG_CODE &&
	(inst_vars.tmp->argv[1][1] < 1 || inst_vars.tmp->argv[1][1] > REG_NUMBER)))
		return ;
	take_bits_params(&inst_vars, map);
	inst_vars.tmp->carry = 0;
	if ((inst_vars.one | inst_vars.two) == 0)
		inst_vars.tmp->carry = 1;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] =
	inst_vars.one | inst_vars.two;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			printf("P%5d | or %d %d r%d\n", cur_proc + 1, inst_vars.one,
			inst_vars.two, inst_vars.tmp->argv[2][1]);
		else
			printf("P%6d | or %d %d r%d\n", cur_proc + 1, inst_vars.one,
			inst_vars.two, inst_vars.tmp->argv[2][1]);
	}
}

void	bit_xor(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_instr inst_vars;

	inst_vars_init(&inst_vars, processes);
	if (inst_vars.tmp->argv[2][0] != REG_CODE || inst_vars.tmp->argv[2][1] < 1
	|| inst_vars.tmp->argv[2][1] > REG_NUMBER || (inst_vars.tmp->argv[0][0] ==
	REG_CODE && (inst_vars.tmp->argv[0][1] < 1 || inst_vars.tmp->argv[0][1] >
	REG_NUMBER)) || (inst_vars.tmp->argv[1][0] == REG_CODE &&
	(inst_vars.tmp->argv[1][1] < 1 || inst_vars.tmp->argv[1][1] > REG_NUMBER)))
		return ;
	take_bits_params(&inst_vars, map);
	inst_vars.tmp->carry = 0;
	if ((inst_vars.one ^ inst_vars.two) == 0)
		inst_vars.tmp->carry = 1;
	inst_vars.tmp->regs[inst_vars.tmp->argv[2][1] - 1] =
	inst_vars.one ^ inst_vars.two;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			printf("P%5d | xor %d %d r%d\n", cur_proc + 1,
			inst_vars.one, inst_vars.two, inst_vars.tmp->argv[2][1]);
		else
			printf("P%6d | xor %d %d r%d\n", cur_proc + 1,
			inst_vars.one, inst_vars.two, inst_vars.tmp->argv[2][1]);
	}
}
