/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:57:23 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/20 13:57:42 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		take_args_and_do_instr(t_proc *processes, t_cycle *main_cycle,
	unsigned char *map, t_flags *params)
{
	if (g_op_tab[(*processes).cmd - 1].codage)
	{
		(*processes).arg_counter = 0;
		(*main_cycle).id_counter = ((*processes).current_position +
		1) % MEM_SIZE;
		take_args(map[(*main_cycle).id_counter], processes);
		get_args_values(processes, map, &main_cycle->id_counter);
	}
	else if (!g_op_tab[(*processes).cmd - 1].codage)
	{
		(*processes).arg_counter = 0;
		(*main_cycle).id_counter = (*processes).current_position;
		(*processes).argv[0][0] = DIR_CODE;
		g_get_arg_vals[(*processes).argv[0][0] - 1](processes, map,
			0, &main_cycle->id_counter);
	}
	if ((*processes).cmd == 1 || (*processes).cmd == 12 ||
		(*processes).cmd == 15)
		g_instruct[(*processes).cmd -
		1]((*main_cycle).head_proc, (*processes).id, main_cycle, map);
	else if ((*processes).cmd != 16 || ((*processes).cmd == 16
		&& (*params).a_aff && !(*params).ncurses))
		g_instruct[(*processes).cmd -
		1](processes, (*processes).id, main_cycle, map);
	return (1);
}

void	change_cur_pos_and_print_it(t_proc *processes, t_cycle *main_cycle,
	t_flags *params, unsigned char *map)
{
	if ((*processes).cmd != 9 || ((*processes).cmd == 9
		&& (*processes).carry == 0))
	{
		(*main_cycle).shift = (*main_cycle).id_counter + 1 -
		(*processes).current_position;
		print_adv(main_cycle, processes, params, map);
	}
	(*processes).current_position = (*processes).current_position % MEM_SIZE;
	(*processes).cmd = map[(*processes).current_position];
	if ((*processes).cmd >= 1 && (*processes).cmd <= CMD_NBR)
		(*processes).cycles_wait = g_op_tab[(*processes).cmd - 1].cycles_wait;
	else
		(*processes).cycles_wait = 1;
	(*main_cycle).indexes[(*processes).current_position % MEM_SIZE][1] = CARETKA;
	clear_argv_arr(processes);
}

void	skip_if_not_cmd(t_cycle *main_cycle, t_proc *processes,
	unsigned char *map)
{
	(*main_cycle).indexes[(*processes).current_position % MEM_SIZE][1] = NO_CARETKA;
	(*processes).current_position++;
	(*processes).current_position = (*processes).current_position % MEM_SIZE;
	(*processes).cmd = map[(*processes).current_position];
	if ((*processes).cmd >= 1 && (*processes).cmd <= CMD_NBR)
		(*processes).cycles_wait = g_op_tab[(*processes).cmd - 1].cycles_wait;
	else
		(*processes).cycles_wait = 1;
	(*main_cycle).indexes[(*processes).current_position % MEM_SIZE][1] = CARETKA;
}

void	internal_cycle_core(t_cycle *main_cycle, t_proc *processes,
	t_flags *params, unsigned char *map)
{
	while (processes)
	{
		if ((*processes).if_live && (*processes).cmd >= 1 &&
		(*processes).cmd <= CMD_NBR && (*processes).cycles_wait == 1)
		{
			take_args_and_do_instr(processes, main_cycle, map, params);
			change_cur_pos_and_print_it(processes, main_cycle, params, map);
		}
		else if ((*processes).if_live && (*processes).cmd >= 1
		&& (*processes).cmd <= CMD_NBR && (*processes).cycles_wait > 1)
			(*processes).cycles_wait--;
		else if ((*processes).if_live && ((*processes).cmd > CMD_NBR
			|| (*processes).cmd < 1))
			skip_if_not_cmd(main_cycle, processes, map);
		(*processes).live_cycle++;
		processes = processes->next;
		(*params).i++;
	}
}

void	start_cycle(unsigned char *map, t_flags *params,
	WINDOW **win, t_cycle *main_cycle)
{
	t_proc		*processes;

	processes = (*main_cycle).head_proc;
	while ((*main_cycle).processes > 0)
	{
		if ((((*params).v_verbosity >> 1) & 1) && !(*params).ncurses)
			printf("%s%d\n", "It is now cycle ", (*main_cycle).cycles + 1);
		processes = (*main_cycle).head_proc;
		if ((*params).ncurses == 1)
		{
			map_to_screen(map, main_cycle, params, *win);
			char_listener(main_cycle, win);
			if ((*main_cycle).run == 0 && (*params).ncurses == 1)
				continue ;
		}
		internal_cycle_core(main_cycle, processes, params, map);
		cycle_period_check(&main_cycle->cycle_counter, main_cycle, params);
		if (!external_cycle_pass(main_cycle, map, params))
			break ;
	}
}
