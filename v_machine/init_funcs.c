/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:05:41 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/13 19:06:43 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	init_bots(t_header bots[MAX_PLAYERS])
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		bots[i].magic = 0;
		bots[i].prog_size = 0;
		bots[i].exec_part = NULL;
		bots[i].start_index = 0;
		bots[i].real_id = 0;
		ft_bzero(bots[i].prog_name, ft_strlen(bots[i].prog_name));
		ft_bzero(bots[i].comment, ft_strlen(bots[i].comment));
		i++;
	}
}

void	params_init(t_flags *params)
{
	int i;

	i = 0;
	(*params).i = 1;
	(*params).j = 0;
	(*params).a_aff = 0;
	(*params).d_dumps_memory = 0;
	(*params).v_verbosity = 0;
	(*params).ncurses = 0;
	(*params).bots_quantity = 0;
	(*params).sum_bots = 0;
	while (i < MAX_PLAYERS)
	{
		(*params).players[i] = NULL;
		i++;
	}
	i = 0;
	while (i < MAX_PLAYERS)
	{
		(*params).pl_nbr[i][0] = 0;
		(*params).pl_nbr[i][1] = -1;
		i++;
	}
}

void	main_cycle_init(t_cycle *main_cycle, t_flags *params)
{
	(*main_cycle).cycles = 0;
	(*main_cycle).processes = (*params).bots_quantity;
	(*main_cycle).second_limit = SEC_LIMIT;
	(*main_cycle).cycle_die = CYCLE_TO_DIE;
	(*main_cycle).current_winner = -1;
	(*main_cycle).checks_if_die = MAX_CHECKS;
	(*main_cycle).winner_str = 0;
	(*main_cycle).winner_name = NULL;
	(*main_cycle).winner_id = -1;
	(*main_cycle).head_proc = NULL;
	(*main_cycle).start_bots = (*params).bots_quantity;
	(*main_cycle).verbose = (*params).v_verbosity;
	(*main_cycle).ncurses = (*params).ncurses;
	(*main_cycle).max_id = 0;
	(*main_cycle).shift = 0;
	(*main_cycle).id_counter = 0;
	(*main_cycle).cycle_counter = 0;
	(*main_cycle).fork_ind = 0;
	(*main_cycle).run = 0;
	(*main_cycle).m = 0;
	(*main_cycle).live_id = 0;
	(*main_cycle).live_name = NULL;
	(*main_cycle).early_exit = 0;
}

void	processes_init2(t_flags *params, t_header bots[MAX_PLAYERS],
	unsigned char *map, t_proc *processes)
{
	clear_argv_arr(processes);
	bots[(*params).i].id = (*processes).id;
	(*processes).real_id = (*params).i;
	bots[(*params).i].real_id = (*processes).real_id;
	(*processes).name = bots[(*params).i].prog_name;
	(*processes).current_position = bots[(*params).i++].start_index;
	(*processes).carry = 0;
	(*processes).parent_nbr = -1;
	(*processes).if_live = 1;
	(*processes).lives = 0;
	(*processes).arg_counter = 0;
	(*processes).cmd = map[(*processes).current_position];
	if ((*processes).cmd >= 1 && (*processes).cmd <= CMD_NBR)
		(*processes).cycles_wait = g_op_tab[(*processes).cmd - 1].cycles_wait;
	else
		(*processes).cycles_wait = 1;
	(*processes).last_live_cycle = 0;
	(*processes).live_cycle = 0;
	(*params).j = 0;
	while ((*params).j < REG_NUMBER)
		(*processes).regs[(*params).j++] = 0;
}

t_proc	*processes_init(t_flags *params, t_header bots[MAX_PLAYERS],
	unsigned char *map)
{
	t_proc			*processes;
	t_proc			*tmp;
	int				cur_id;

	(*params).i = 0;
	tmp = NULL;
	cur_id = 0;
	while ((*params).i < (*params).bots_quantity)
	{
		processes = (t_proc *)malloc(sizeof(t_proc));
		if ((*params).pl_nbr[(*params).i][0])
			(*processes).id = (*params).pl_nbr[(*params).i][1] - 1;
		else
		{
			while (check_if_norepeat_id(params, cur_id, 0))
				cur_id++;
			(*processes).id = cur_id;
			cur_id++;
		}
		(*processes).next = tmp;
		processes_init2(params, bots, map, processes);
		(*processes).regs[0] = (unsigned int)(((*processes).id + 1) * -1);
		tmp = processes;
	}
	return (processes);
}
