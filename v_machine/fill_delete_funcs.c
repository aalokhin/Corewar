/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_delete_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:41:43 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 16:44:34 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	clear_argv_arr(t_proc *processes)
{
	(*processes).argv[0][0] = 0;
	(*processes).argv[0][1] = 0;
	(*processes).argv[1][0] = 0;
	(*processes).argv[1][1] = 0;
	(*processes).argv[2][0] = 0;
	(*processes).argv[2][1] = 0;
}

void	delete_unneeded(t_proc **head, t_cycle *main_cycle)
{
	t_proc *prev;
	t_proc *tmp;

	tmp = *head;
	prev = tmp;
	while (tmp != NULL && (tmp->if_live == 0 || (*main_cycle).cycles <= 0))
	{
		*head = tmp->next;
		free(tmp);
		tmp = *head;
	}
	while (tmp != NULL)
	{
		while (tmp != NULL && (tmp->if_live != 0 || (*main_cycle).cycles > 0))
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

void	fill_start_map_id(t_cycle *main_cycle, header_t bots[4],
	t_flags *params)
{
	unsigned int	k;

	(*params).i = 0;
	(*params).j = 0;
	k = 0;
	while ((*params).i < MEM_SIZE)
	{
		(*main_cycle).indexes[(*params).i][0] = 0;
		(*main_cycle).indexes[(*params).i++][1] = 0;
	}
	(*params).i = 0;
	while ((*params).i < MEM_SIZE && (*params).j < (*params).bots_quantity)
	{
		if ((unsigned int)(*params).i == bots[(*params).j].start_index)
		{
			(*main_cycle).indexes[(*params).i][1] = 1;
			k = 0;
			while (k++ < bots[(*params).j].prog_size)
				(*main_cycle).indexes[(*params).i++][0] = (*params).j + 1;
			(*params).j++;
		}
		(*params).i++;
	}
}
