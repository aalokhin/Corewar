/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_mat_jump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:33:43 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 16:00:20 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	live_dir_proc(t_proc *child_proc, t_proc *head_proc,
	t_cycle *main_cycle)
{
	t_proc *tmp;

	tmp = head_proc;
	(*child_proc).argv[0][1] = ((*child_proc).argv[0][1] * -1) - 1;
	if ((*child_proc).argv[0][1] <= (*head_proc).id)
	{
		while (tmp && (*tmp).id != (*child_proc).argv[0][1])
			tmp = tmp->next;
		if (tmp)
		{
			if ((*tmp).if_live)
				(*tmp).last_live_cycle = (*main_cycle).cycles;
			if (((*main_cycle).verbose & 1) && !(*main_cycle).ncurses)
				ft_printf("Player %d (%s) is said to be alive\n",
				(*child_proc).argv[0][1] + 1, (*tmp).name);
				//ft_printf("A process shows that player %d (%s) is alive\n",
				//(*child_proc).argv[0][1] + 1, (*tmp).name);
		}
	}
}

void	live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc *child_proc;

	child_proc = head_proc;
	while (child_proc && (*child_proc).id != cur_proc)
		child_proc = child_proc->next;
	(*child_proc).if_live = 1;
	(*child_proc).last_live_cycle = (*main_cycle).cycles;
	(*child_proc).lives++;
	(*child_proc).live_cycle = 0;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if ((*child_proc).id + 1 <= 9999)
			ft_printf("P%5d | live %d\n", (*child_proc).id + 1,
		(*child_proc).argv[0][1]);
		else
			ft_printf("P%6d | live %d\n", (*child_proc).id + 1,
			(*child_proc).argv[0][1]);
	}
	if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] <= 0
		&& (*child_proc).argv[0][1] >= -255)
		live_dir_proc(child_proc, head_proc, main_cycle);
	map[0] = map[0];
}

void	addition(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc	*tmp;

	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE
	|| (*tmp).argv[2][0] != REG_CODE || (*tmp).argv[0][1] < 0 ||
	(*tmp).argv[0][1] > REG_NUMBER || (*tmp).argv[1][1] < 0 || (*tmp).argv[1][1]
	> REG_NUMBER || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > REG_NUMBER)
		return ;
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] +
		(*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | add r%d r%d r%d\n", cur_proc + 1,
			(*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
		else
			ft_printf("P%6d | add r%d r%d r%d\n", cur_proc + 1,
			(*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	}
	map[0] = map[0];
}

void	substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc	*tmp;

	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE
	|| (*tmp).argv[2][0] != REG_CODE || (*tmp).argv[0][1] < 0 ||
	(*tmp).argv[0][1] > REG_NUMBER || (*tmp).argv[1][1] < 0 || (*tmp).argv[1][1]
	> REG_NUMBER || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > REG_NUMBER)
		return ;
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] -
		(*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | sub r%d r%d r%d\n", cur_proc + 1,
			(*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
		else
			ft_printf("P%6d | sub r%d r%d r%d\n", cur_proc + 1,
			(*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	}
	map[0] = map[0];
}

void	zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc	*tmp;
	char	*res;

	res = "FAILED";
	tmp = processes;
	if ((*tmp).carry == 1)
	{
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] =
		NO_CARETKA;
		(*tmp).current_position += ((*tmp).argv[0][1] % IDX_MOD);
		(*tmp).current_position = (((*tmp).current_position % MEM_SIZE)
		+ MEM_SIZE) % MEM_SIZE;
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 1;
		res = "OK";
	}
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if (cur_proc + 1 <= 9999)
			ft_printf("P%5d | zjmp %d %s\n", cur_proc + 1,
				(*tmp).argv[0][1], res);
		else
			ft_printf("P%6d | zjmp %d %s\n", cur_proc + 1,
				(*tmp).argv[0][1], res);
	}
	map[0] = map[0];
}
