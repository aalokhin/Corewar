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

int		live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	t_proc *tmp;
	t_proc *child_proc;

	tmp = head_proc;
	child_proc = head_proc;
	while (child_proc && (*child_proc).id != cur_proc)
		child_proc = child_proc->next;
	(*child_proc).if_live = 1;
	(*child_proc).last_live_cycle = (*main_cycle).cycles;
	(*child_proc).lives++;
	(*child_proc).live_cycle = 0;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | live %d\n", (*child_proc).id + 1,
		(*child_proc).argv[0][1]);
	if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] <= 0)
	{
		(*child_proc).argv[0][1] = ((*child_proc).argv[0][1] * -1) - 1;
		if ((*child_proc).argv[0][1] <= (*head_proc).id)
		{
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

int		addition(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE
		|| (*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 ||
		(*tmp).argv[1][1] < 0 || (*tmp).argv[1][1] > 16 ||
		(*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] +
		(*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | add r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
		(*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int		substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE ||
		(*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1]
	< 0 || (*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 ||
	(*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] -
		(*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | sub r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
			(*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int		zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;
	char	*res;

	i = 0;
	res = "FAILED";
	tmp = processes;
	if ((*tmp).carry == 1)
	{
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 0;
		(*tmp).current_position += ((*tmp).argv[0][1] % IDX_MOD);
		(*tmp).current_position = ((*tmp).current_position + MEM_SIZE)
		% MEM_SIZE;
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 1;
		res = "OK";
	}
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | zjmp %d %s\n", cur_proc + 1, (*tmp).argv[0][1], res);
	map[0] = map[0];
	return (1);
}