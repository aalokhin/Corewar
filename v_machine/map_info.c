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
	mvwprintw(win, y, x, "MAX_CHECKS : %d", MAX_CHECKS);
	y += 2;
	if ((*main_cycle).winner_name)
		mvwprintw(win, y, x, "Current winner is : %s",
		(*main_cycle).winner_name);
	(*main_cycle).winner_str = y + 2;
	wrefresh(win);
}

void	print_map_info(WINDOW *win, t_cycle *main_cycle, t_flags *params)
{
	int		x;
	int		y;
	int		tmp;
	t_proc	*processes;

	x = 199;
	y = 9;
	processes = (*main_cycle).head_proc;
	wrefresh(win);
	while ((*processes).real_id != (*params).bots_quantity - 1)
		processes = processes->next;
	y = y + (4 * (*params).bots_quantity);
	tmp = y;
	x += 2;
	while (processes)
	{
		mvwprintw(win, y, x, "Lives in current period : %d ",
			(*processes).lives);
		y -= 1;
		mvwprintw(win, y, x, "Last live: %d ", (*processes).last_live_cycle);
		y -= 3;
		processes = processes->next;
	}
	print_map_info2(win, main_cycle, x - 2, tmp + 3);
}
