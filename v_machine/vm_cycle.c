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

void	take_args_and_do_instr(t_proc *processes, t_cycle *main_cycle,
	unsigned char *map, t_flags *params)
{
	if (g_op_tab[(*processes).cmd - 1].codage)
	{
		(*main_cycle).id_counter = ((*processes).current_position +
		1 + MEM_SIZE) % MEM_SIZE;
		take_args(map[(*main_cycle).id_counter], processes);
		get_args_values(processes, map, &main_cycle->id_counter);
		(*processes).arg_counter = 0;
	}
	else
	{
		(*main_cycle).id_counter = (*processes).current_position;
		(*processes).argv[0][0] = DIR_CODE;
		g_get_arg_vals[(*processes).argv[0][0] - 1](processes, map,
			0, &main_cycle->id_counter);
		(*processes).arg_counter = 0;
	}
	if ((*processes).cmd == 1 || (*processes).cmd == 12 ||
		(*processes).cmd == 15)
		(*main_cycle).instr_res = g_instruct[(*processes).cmd -
		1]((*main_cycle).head_proc, (*processes).id, main_cycle, map);
	else if ((*processes).cmd != 16 || ((*processes).cmd == 16
		&& (*params).a_aff))
		(*main_cycle).instr_res = g_instruct[(*processes).cmd -
		1](processes, (*processes).id, main_cycle, map);
		//printf("RES%d\n", (*main_cycle).instr_res = 0);
}

void	change_cur_pos_and_print_it(t_proc *processes, t_cycle *main_cycle,
	t_flags *params, unsigned char *map)
{

	/*if ((*processes).cmd == 1 || (*processes).cmd == 12 ||
		(*processes).cmd == 15 || ((*processes).cmd == 9 &&
	(*processes).carry == 0))
		{
			if(!g_op_tab[(*processes).cmd - 1].label)
				(*main_cycle).shift = 5;
			else
			(*main_cycle).shift = 3;
			print_adv(main_cycle, processes, params, map);
		}
	else if ((*processes).cmd != 9
&& (*main_cycle).id_counter + 1 - (*processes).current_position != 0)
	{
		(*main_cycle).shift = (*main_cycle).id_counter + 1 -
		(*processes).current_position;
		print_adv(main_cycle, processes, params, map);
	}*/
	if (((*processes).cmd == 3 || (*processes).cmd == 2 ) && (*main_cycle).instr_res == 0
	/* && (*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr*/)
	{
		(*main_cycle).shift = 2;
		print_adv(main_cycle, processes, params, map);
	}
	else if ((*processes).cmd != 9 || ((*processes).cmd == 9 && (*processes).carry == 0))/* || (*processes).cmd == 1
		|| (*processes).cmd == 12 || (*processes).cmd == 15)*/
	{
		(*main_cycle).shift = (*main_cycle).id_counter + 1 -
		(*processes).current_position;
		print_adv(main_cycle, processes, params, map);
	}
	(*processes).current_position = ((*processes).current_position +
		MEM_SIZE) % MEM_SIZE;
	(*processes).cmd = map[(*processes).current_position];
	if ((*processes).cmd >= 1 && (*processes).cmd <= CMD_NBR)
		(*processes).cycles_wait = g_op_tab[(*processes).cmd - 1].cycles_wait;
	else
		(*processes).cycles_wait = 1;
	(*main_cycle).indexes[(*processes).current_position][1] = CARETKA;
	clear_argv_arr(processes);
}

void	skip_if_not_cmd(t_cycle *main_cycle, t_proc *processes,
	unsigned char *map)
{
	(*main_cycle).indexes[(*processes).current_position][1] = NO_CARETKA;
	(*processes).current_position++;
	(*processes).current_position = ((*processes).current_position
	+ MEM_SIZE) % MEM_SIZE;
	(*processes).cmd = map[(*processes).current_position];
	if ((*processes).cmd >= 1 && (*processes).cmd <= CMD_NBR)
		(*processes).cycles_wait = g_op_tab[(*processes).cmd - 1].cycles_wait;
	else
		(*processes).cycles_wait = 1;
	(*main_cycle).indexes[(*processes).current_position][1] = CARETKA;
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
			(*main_cycle).shift = 2;
			change_cur_pos_and_print_it(processes, main_cycle, params, map);
		}
		else if ((*processes).if_live && (*processes).cmd >= 1
		&& (*processes).cmd <= CMD_NBR && (*processes).cycles_wait > 1)
			(*processes).cycles_wait--;
		else if ((*processes).if_live)
			skip_if_not_cmd(main_cycle, processes, map);
		(*processes).live_cycle++;
		processes = processes->next;
		(*params).i++;
	}
}

void speed_listener(char spc, t_cycle *main_cycle, WINDOW **win)
{
	if (spc == 'q')
	{
			(*main_cycle).second_limit -= 10;
			if ((*main_cycle).second_limit <= 0)
					(*main_cycle).second_limit = 1;
			mvwprintw(*win, 4, 199,  "Cycles/second limit : %d\n", (*main_cycle).second_limit);
			wrefresh(*win);
	}
	if (spc == 'w')
	{
			(*main_cycle).second_limit -= 1;
			if ((*main_cycle).second_limit <= 0)
					(*main_cycle).second_limit = 1;
			mvwprintw(*win, 4, 199,  "Cycles/second limit : %d\n", (*main_cycle).second_limit);
			wrefresh(*win);
	}
	if (spc == 'e')
	{
			(*main_cycle).second_limit += 1;
			mvwprintw(*win, 4, 199,  "Cycles/second limit : %d\n", (*main_cycle).second_limit);
			wrefresh(*win);
	}
	if (spc == 'r')
	{
			(*main_cycle).second_limit += 10;
			mvwprintw(*win, 4, 199,  "Cycles/second limit : %d\n", (*main_cycle).second_limit);
			wrefresh(*win);
	}
}

void    vm_cycle(unsigned char *map, t_flags *params, t_header bots[4])
{
    t_cycle    main_cycle;
    t_proc    *processes;
    char     spc;

    WINDOW * win;
    spc = '\0';
    win = NULL;
    processes = NULL;
    main_cycle_init(&main_cycle, params);
    fill_start_map_id(&main_cycle, bots, params);
    processes = processes_init(params, bots, map);
    main_cycle.head_proc = processes;
    intro_print(params, bots, &win, processes);
    mvwprintw(win, 2, 199,  "** PAUSED **");
    curs_set(0);
    while (main_cycle.processes > 0)
    {
        if (((*params).v_verbosity >> 1) & 1)
            printf("%s%d\n", "It is now cycle ", main_cycle.cycles + 1);
        processes = main_cycle.head_proc;
        if ((*params).ncurses == 1)
            map_to_screen(map, &main_cycle, params, main_cycle.head_proc, win);
        if (main_cycle.run == 1)
        {
            spc = (char)getch();
            if (spc == ' ')
            {
                main_cycle.run = 0;
                mvwprintw(win, 2, 199,  "** PAUSED **\n");
                wrefresh(win);
                nodelay(stdscr, FALSE);
            }
            speed_listener(spc, &main_cycle, &win);
        }
        else
        {
            spc = (char)getch();
            if (spc == ' ')
            {
                main_cycle.run = 1;
                mvwprintw(win, 2, 199,  "** RUNNING **");
                wrefresh(win);
                nodelay(stdscr, TRUE);
            }
						speed_listener(spc, &main_cycle, &win);
        }
        internal_cycle_core(&main_cycle, processes, params, map);
        cycle_period_check(&main_cycle.cycle_counter, &main_cycle, params);

        if (!external_cycle_pass(&main_cycle, map, params))
            break ;
    }
    after_cycle(params, bots, main_cycle, win);
}
