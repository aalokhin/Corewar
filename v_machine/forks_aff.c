/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:37:55 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/15 17:52:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	inst_vars_init(t_instr *inst_vars, t_proc *processes)
{
	(*inst_vars).i = 0;
	(*inst_vars).one = 0;
	(*inst_vars).two = 0;
	(*inst_vars).tmp = processes;
	(*inst_vars).new_ind = 0;
}

void	ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;
	t_proc	*head;

	i = 0;
	tmp = processes;
	head = processes;
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if ((*tmp).id + 1 <= 9999)
			ft_printf("P%5d | fork %d (%d)\n",
				(*tmp).id + 1, (*tmp).argv[0][1], i);
		else
			ft_printf("P%6d | fork %d (%d)\n",
				(*tmp).id + 1, (*tmp).argv[0][1], i);
	}
	i = ((i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
	(*main_cycle).fork_ind = i;
	processes_add(&head, map, main_cycle, cur_proc);
}

void	long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;
	t_proc	*head;

	i = 0;
	tmp = processes;
	head = processes;
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).argv[0][1] + (*tmp).current_position;
	if ((((*main_cycle).verbose >> 2) & 1) && !(*main_cycle).ncurses)
	{
		if ((*tmp).id + 1 <= 9999)
			ft_printf("P%5d | lfork %d (%d)\n", (*tmp).id + 1,
			(*tmp).argv[0][1], i);
		else
			ft_printf("P%6d | lfork %d (%d)\n", (*tmp).id + 1,
			(*tmp).argv[0][1], i);
	}
	i = ((i % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
	(*main_cycle).fork_ind = i;
	processes_add(&head, map, main_cycle, cur_proc);
}

void	aff(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1
		|| (*tmp).argv[0][1] > REG_NUMBER)
		return ;
	ft_printf("%s", "Aff: ");
	ft_printf("%c\n", ((*tmp).regs[(*tmp).argv[0][1] - 1] % 256));
	(*main_cycle).cycles = (*main_cycle).cycles;
	cur_proc = map[0];
}

void	insert_vals_to_map(unsigned char *map, t_instr inst_vars,
	t_cycle *main_cycle)
{
	map[(inst_vars.i + 3) % MEM_SIZE] =
	(inst_vars.tmp->regs[inst_vars.tmp->argv[0][1] - 1] & 0x000000FF);
	map[(inst_vars.i + 2) % MEM_SIZE] =
	(inst_vars.tmp->regs[inst_vars.tmp->argv[0][1] - 1] & 0x0000FF00)
	>> 8;
	map[(inst_vars.i + 1) % MEM_SIZE] =
	(inst_vars.tmp->regs[inst_vars.tmp->argv[0][1] - 1] & 0x00FF0000)
	>> 16;
	map[inst_vars.i % MEM_SIZE] =
	(inst_vars.tmp->regs[inst_vars.tmp->argv[0][1] - 1]
		& 0xFF000000) >> 24;
	inst_vars.new_ind = inst_vars.tmp->parent_nbr + 1;
	if (inst_vars.tmp->parent_nbr == -1)
		inst_vars.new_ind = inst_vars.tmp->real_id + 1;
	(*main_cycle).indexes[inst_vars.i % MEM_SIZE][0] =
	inst_vars.new_ind;
	(*main_cycle).indexes[(inst_vars.i + 1) % MEM_SIZE][0] =
	inst_vars.new_ind;
	(*main_cycle).indexes[(inst_vars.i + 2) % MEM_SIZE][0] =
	inst_vars.new_ind;
	(*main_cycle).indexes[(inst_vars.i + 3) % MEM_SIZE][0] =
	inst_vars.new_ind;
}
