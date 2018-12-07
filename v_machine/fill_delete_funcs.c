/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_delete_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:41:43 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/20 13:53:20 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	get_args_value(int arg_size, unsigned int *dest, unsigned char *map,
	int *id_counter)
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

void	processes_add2(t_proc **head, t_cycle *main_cycle,
	t_proc *tmp, t_proc *parent)
{
	if ((**head).id == 0)
		tmp->id = (*main_cycle).start_bots;
	else if ((*main_cycle).max_id <= (**head).real_id)
		tmp->id = (**head).real_id + 1;
	else
		tmp->id = (*main_cycle).max_id + 1;
	tmp->real_id = (**head).real_id + 1;
	tmp->name = (*parent).name;
	tmp->carry = (*parent).carry;
	if ((*parent).parent_nbr == -1)
		tmp->parent_nbr = (*parent).real_id;
	else
		tmp->parent_nbr = (*parent).parent_nbr;
	tmp->if_live = 1;
	tmp->last_live_cycle = 0;
	tmp->child_proc_lives = 0;
	tmp->live_cycle = (*parent).live_cycle + 1;
	clear_argv_arr(tmp);
	(*main_cycle).max_id = tmp->id;
	tmp->next = *head;
	*head = tmp;
	(*main_cycle).head_proc = *head;
	tmp->current_position = (*main_cycle).fork_ind;
}

void	processes_add(t_proc **head, unsigned char *map,
	t_cycle *main_cycle, int cur_proc)
{
	t_proc	*tmp;
	t_proc	*parent;
	int		j;

	j = 0;
	tmp = NULL;
	parent = *head;
	(*main_cycle).processes++;
	while (parent && (*parent).id != cur_proc)
		parent = parent->next;
	tmp = (t_proc *)malloc(sizeof(t_proc));
	processes_add2(head, main_cycle, tmp, parent);
	tmp->arg_counter = 0;
	tmp->cmd = map[tmp->current_position];
	(*main_cycle).indexes[(*main_cycle).fork_ind % MEM_SIZE][1] =
	CARETKA;
	if (tmp->cmd >= 1 && tmp->cmd <= CMD_NBR)
		tmp->cycles_wait = g_op_tab[tmp->cmd - 1].cycles_wait;
	else
		tmp->cycles_wait = 1;
	while (j < REG_NUMBER)
	{
		tmp->regs[j] = (*parent).regs[j];
		j++;
	}
}

void	clear_argv_arr(t_proc *processes)
{
	int i;

	i = 0;
	while (i < MAX_ARGS_NUMBER - 1)
	{
		(*processes).argv[i][0] = 0;
		(*processes).argv[i][1] = 0;
		i++;
	}
}

//void	delete_unneeded(t_proc **head, t_cycle *main_cycle,
	//int early_exit)
void	delete_unneeded(t_proc **head, t_cycle *main_cycle)
{
	t_proc *prev;
	t_proc *tmp;

	tmp = *head;
	prev = tmp;
	// while (tmp != NULL && (!tmp->if_live ||
	// 	(*main_cycle).cycles <= 0 || early_exit))
	while (tmp != NULL && (!tmp->if_live || (*main_cycle).cycles <= 0))
	{
		*head = tmp->next;
		free(tmp);
		tmp = *head;
	}
	while (tmp != NULL)
	{
		while (tmp != NULL && (tmp->if_live || (*main_cycle).cycles > 0))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return ;
		prev->next = tmp->next;
		tmp = prev->next;
	}
}
