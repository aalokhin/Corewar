/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualastia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:08:30 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/04 18:09:17 by vlikhotk         ###   ########.fr       */
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

void	print_winner(WINDOW **win, t_cycle *main_cycle)
{
	int		x;
	int		y;
	char	c;

	x = 199;
	y = (*main_cycle).winner_str;
	wattron(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
	mvwprintw(*win, y, x, "The winner is : %s", (*main_cycle).winner_name);
	wattroff(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
	y += 2;
	mvwprintw(*win, y, x, "Press any key for exit");
	wrefresh(*win);
	nodelay(stdscr, FALSE);
	c = (char)getch();
	wclear(*win);
	endwin();
}

void	init_colors(WINDOW **win)
{
	init_pair(12, COLOR_CYAN, COLOR_CYAN);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_RED);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_BLUE);
	init_pair(33, COLOR_BLACK, COLOR_RED);
	init_pair(44, COLOR_BLACK, COLOR_CYAN);
	init_pair(55, COLOR_BLACK, COLOR_WHITE);
	wattron(*win, COLOR_PAIR(12));
	wborder(*win, 42, 42, 42, 42, 42, 42, 42, 42);
	mvwvline(*win, 1, 196, 42, 70);
	wattroff(*win, COLOR_PAIR(12));
}

void	visual_init(WINDOW **win, t_flags *params,
	t_header bots[MAX_PLAYERS], t_cycle *main_cycle)
{
	int i;
	int x;
	int y;

	x = 199;
	y = 9;
	i = 0;
	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
	*win = newwin(68, 0, 0, 5);
	init_colors(win);
	mvwprintw(*win, 2, 199, "** PAUSED **");
	mvwprintw(*win, 45, 199, "=============> MUSIC OFF <============== %d, ",
	(*main_cycle).m);
	while (i < (*params).bots_quantity)
	{
		y += 2;
		mvwprintw(*win, y, x, "Player: -%d : %s",
			bots[i].id + 1, bots[i].prog_name);
		i++;
		y += 2;
	}
}

void	map_to_screen(unsigned char *map, t_cycle *main_cycle,
	t_flags *params, WINDOW *win)
{
	int i;
	int y;
	int x;
	int res;

	i = 0;
	y = 2;
	x = 3;
	res = 0;
	refresh();
	while (i < MEM_SIZE)
	{
		x = 3;
		while (x < 194)
		{
			if ((*main_cycle).indexes[i][0] >= 1 &&
				(*main_cycle).indexes[i][0] <= (*params).bots_quantity)
				res = (*main_cycle).indexes[i][0];
			else
				res = 5;
			if ((*main_cycle).indexes[i][1] == CARETKA)
			{
				wattron(win, COLOR_PAIR(res * 11));
				mvwprintw(win, y, x, "%.2x", map[i]);
				wattroff(win, COLOR_PAIR(res * 11));
			}
			else
			{
				wattron(win, COLOR_PAIR(res));
				mvwprintw(win, y, x, "%.2x", map[i]);
				wattroff(win, COLOR_PAIR(res));
			}
			x += 3;
			i++;
		}
		print_map_info(win, main_cycle, params);
		y++;
	}
}
