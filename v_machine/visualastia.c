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

void	print_winner(WINDOW **win, t_cycle *main_cycle)
{
	int		x;
	int		y;
	char	c;

	x = 199;
	y = (*main_cycle).winner_str;
	if ((*main_cycle).winner_id >= 0)
	{
		wattron(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
		mvwprintw(*win, y, x, "Player %d (%s) won",
			(*main_cycle).winner_id + 1, (*main_cycle).winner_name);
		wattroff(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
	}
	else
		mvwprintw(*win, y, x,
			"There is no winner in this game. Friendship won:)");
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
	mvwprintw(*win, 2, 199, "** PAUSED **");
}

void	visual_init(WINDOW **win, t_flags *params,
	t_header bots[MAX_PLAYERS])
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
	while (i < (*params).bots_quantity)
	{
		y += 2;
		wattron(*win, COLOR_PAIR(bots[i].real_id + 1));
		mvwprintw(*win, y, x, "Player: -%d : %s",
			bots[i].id + 1, bots[i].prog_name);
		wattroff(*win, COLOR_PAIR(bots[i].real_id + 1));
		i++;
		y += 3;
	}
}

int		id_count(t_cycle *main_cycle, t_flags *params, int i)
{
	if ((*main_cycle).indexes[i][0] >= 1 &&
		(*main_cycle).indexes[i][0] <= (*params).bots_quantity)
		return ((*main_cycle).indexes[i][0]);
	else
		return (5);
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
	res = 0;
	refresh();
	while (i < MEM_SIZE)
	{
		x = 3;
		while (x < 194 && i < MEM_SIZE)
		{
			res = id_count(main_cycle, params, i);
			if ((*main_cycle).indexes[i][1] == CARETKA)
				res = id_count(main_cycle, params, i) * 11;
			wattron(win, COLOR_PAIR(res));
			mvwprintw(win, y, x, "%.2x", map[i++]);
			wattroff(win, COLOR_PAIR(res));
			x += 3;
		}
		print_map_info(win, main_cycle, params);
		y++;
	}
}
