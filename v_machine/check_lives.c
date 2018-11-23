/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:56:57 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/20 13:57:01 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	live_or_die(t_proc *tmp, t_cycle *main_cycle, t_flags *params,
	int *res)
{
	if ((*tmp).lives == 0 && (*tmp).if_live && (*tmp).live_cycle >
		(*main_cycle).cycle_die)
	{
		(*tmp).if_live = 0;
		(*main_cycle).processes--;
		(*tmp).lives = 0;
		if ((*tmp).id > (*main_cycle).max_id)
			(*main_cycle).max_id = (*tmp).id;
		(*main_cycle).indexes[((*tmp).current_position + MEM_SIZE) % MEM_SIZE][1] = 0;
		if (((*params).v_verbosity >> 3) & 1)
			printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				(*tmp).id + 1, (*tmp).live_cycle - 1,
				(*main_cycle).cycle_die);
	}
	else
	{
		*res += (*tmp).lives;
		(*tmp).lives = 0;
	}
}

int		check_if_lives(t_cycle *main_cycle, t_flags *params)
{
	int		res;
	t_proc	*tmp;
	t_proc	*tmp2;

	res = 0;
	tmp = (*main_cycle).head_proc;
	tmp2 = (*main_cycle).head_proc;
	while (tmp)
	{
		if ((*tmp).last_live_cycle > (*main_cycle).current_winner)
		{
			(*main_cycle).current_winner = (*tmp).last_live_cycle;
			if ((*tmp).parent_nbr == -1)
				(*main_cycle).winner_id = (*tmp).id;
			else
				(*main_cycle).winner_id = (*tmp).parent_nbr;
			(*main_cycle).winner_name = (*tmp).name;
		}
		live_or_die(tmp, main_cycle, params, &res);
		tmp = tmp->next;
	}
	delete_unneeded(&main_cycle->head_proc, main_cycle);
	return (res);
}

void	cycle_period_check(int *cycle_counter, t_cycle *main_cycle,
	t_flags *params)
{
	if (++(*cycle_counter) == (*main_cycle).cycle_die ||
		(*main_cycle).cycle_die < 0)
	{
		*cycle_counter = 0;
		if (check_if_lives(&(*main_cycle), params) >= NBR_LIVE ||
			(*main_cycle).checks_if_die == 0)
		{
			(*main_cycle).cycle_die -= CYCLE_DELTA;
			(*main_cycle).checks_if_die = MAX_CHECKS;
			if (((*params).v_verbosity >> 1) & 1)
				printf("%s%d\n", "Cycle to die is now ",
					(*main_cycle).cycle_die);
		}
		(*main_cycle).checks_if_die--;
	}
}
