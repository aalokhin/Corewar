/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:05:18 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/04 19:05:19 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	print_map_info3(WINDOW *win, t_cycle *main_cycle, int x, int y)
{
	if ((*main_cycle).winner_name)
	{
		wattron(win, COLOR_PAIR((*main_cycle).winner_id + 1));
		mvwprintw(win, y, x, "Current winner is : %s",
		(*main_cycle).winner_name);
		wattroff(win, COLOR_PAIR((*main_cycle).winner_id + 1));
	}
	wrefresh(win);
}

void	print_map_info2(WINDOW *win, t_cycle *main_cycle, int x, int y)
{
	int x_0;
	int y_0;

	x_0 = 199;
	y_0 = 4;
	mvwprintw(win, y_0, x_0, "Cycles/second limit : %d",
		(*main_cycle).second_limit);
	y_0 += 3;
	mvwprintw(win, y_0, x_0, "Cycles: %d", (*main_cycle).cycles);
	y_0 += 2;
	mvwprintw(win, y_0, x_0, "Processes: %d", (*main_cycle).processes);
	mvwprintw(win, y, x, "CYCLE_TO_DIE : %d", (*main_cycle).cycle_die);
	y += 2;
	mvwprintw(win, y, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	mvwprintw(win, y, x, "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win, y, x, "MAX_CHECKS : %d", (*main_cycle).checks_if_die);
	y += 2;
	print_map_info3(win, main_cycle, x, y);
	(*main_cycle).winner_str = y + 2;
	wrefresh(win);
}

void	print_map_info4(WINDOW *win, t_proc *processes, int x, int *y)
{
	if (!(*processes).if_live)
	{
		{
			wattron(win, COLOR_PAIR((*processes).id + 1));
			mvwprintw(win, *y, x, "PROCESS DIED");
			wattroff(win, COLOR_PAIR((*processes).id + 1));
		}
	}
	(*y) -= 2;
	mvwprintw(win, (*y), x, "Lives in current period : %d ",
		(*processes).lives);
	(*y)--;
	wrefresh(win);
	mvwprintw(win, (*y), x, "Last live: %d ", (*processes).last_live_cycle);
	wrefresh(win);
	(*y) += 2;
}

void	print_map_info(WINDOW *win, t_cycle *main_cycle, t_flags *params)
{
	int		x;
	int		y;
	t_proc	*processes;

	x = 201;
	y = 9 + (6 * (*params).bots_quantity);
	processes = (*main_cycle).head_proc;
	while ((*processes).real_id != (*params).bots_quantity - 1)
		processes = processes->next;
	while (processes)
	{
		print_map_info4(win, processes, x, &y);
		if ((*processes).last_live_cycle ==
			(*main_cycle).cycles - 1 && (*main_cycle).cycles != 1)
		{
			wattron(win, COLOR_PAIR((*processes).id + 1));
			mvwprintw(win, y, x,
				"A process shows that player %d (%s) is alive in cycle %d",
			(*processes).id + 1, (*processes).name, (*main_cycle).cycles - 1);
			wattroff(win, COLOR_PAIR((*processes).id + 1));
		}
		y -= 5;
		processes = processes->next;
	}
	print_map_info2(win, main_cycle, x - 2, 11 + (6 * (*params).bots_quantity));
}
