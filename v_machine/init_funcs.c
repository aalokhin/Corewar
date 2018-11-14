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

void	init_bots(header_t bots[4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		bots[i].magic = 0;
		bots[i].prog_size = 0;
		bots[i].exec_part = NULL;
		bots[i].start_index = 0;
		ft_bzero(bots[i].prog_name, ft_strlen(bots[i].prog_name));
		ft_bzero(bots[i].comment, ft_strlen(bots[i].comment));
		i++;
	}
}

void	params_init(t_flags *params)
{
	(*params).a_aff = -1;
	(*params).d_dumps_memory = -1;
	(*params).s_cycles = -1;
	(*params).v_verbosity = -1;
	(*params).binary = -1;
	(*params).b_stealth = -1;
	(*params).ncurses = -1;
	(*params).n_stealth = -1;
	(*params).bots_quantity = 0;
	(*params).players[0] = NULL;
	(*params).players[1] = NULL;
	(*params).players[2] = NULL;
	(*params).players[3] = NULL;
}

void	main_cycle_init(t_cycle *main_cycle, t_flags *params)
{
	(*main_cycle).cycles = 0;
	(*main_cycle).processes = (*params).bots_quantity;
	(*main_cycle).prev_processes = (*main_cycle).processes;
	(*main_cycle).second_limit = 100;
	(*main_cycle).cycle_die = CYCLE_TO_DIE;
	(*main_cycle).current_winner = -1;
	(*main_cycle).checks_if_die = MAX_CHECKS;
	(*main_cycle).prev_cycle_die = (*main_cycle).cycle_die;
	(*main_cycle).winner_str = 0;
	(*main_cycle).winner_name = NULL;
	(*main_cycle).winner_id = 0;
	(*main_cycle).head_proc = NULL;
	(*main_cycle).start_bots = (*params).bots_quantity;
	(*main_cycle).verbose = (*params).v_verbosity;
}

t_proc	*processes_init(t_flags *params, header_t bots[4], unsigned char *map)
{
	unsigned int	i;
	int				j;
	t_proc			*processes;
	t_proc			*tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	while (i < (*params).bots_quantity)
	{
		j = 0;
		processes = (t_proc *)malloc(sizeof(t_proc));
		(*processes).id = i;
		(*processes).name = bots[i].prog_name;
		(*processes).current_position = bots[i++].start_index;
		(*processes).carry = 0;
		(*processes).parent_nbr = -1;
		(*processes).if_live = 1;
		(*processes).lives = 0;
		(*processes).cmd = map[(*processes).current_position];
		if ((*processes).cmd >= 1 && (*processes).cmd <= 16)
			(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
		else
			(*processes).cycles_wait = 1;
		(*processes).last_live_cycle = 0;
		(*processes).live_cycle = 0;
		(*processes).next = tmp;
		clear_argv_arr(processes);
		while (j < REG_NUMBER)
			(*processes).regs[j++] = 0;
		(*processes).regs[0] = (unsigned int)(((*processes).id + 1) * -1);
		tmp = processes;
	}
	return (processes);
}

void	clear_argv_arr(t_proc *processes)
{
	(*processes).argv[0][0] = 0;
	(*processes).argv[0][1] = 0;
	(*processes).argv[1][0] = 0;
	(*processes).argv[1][1] = 0;
	(*processes).argv[2][0] = 0;
	(*processes).argv[2][1] = 0;
}
