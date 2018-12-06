/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:14:10 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/03 18:19:47 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	music_stop_pause(t_cycle *main_cycle, WINDOW **win)
{
	if ((*main_cycle).m == 0)
	{
		system("afplay  media/Game_of_Thrones.mp3 &> /dev/null &");
		(*main_cycle).m = 1;
		mvwprintw(*win, (*main_cycle).winner_str + 10, 199,
			"=============> MUSIC  start <==============");
		wrefresh(*win);
	}
	else if ((*main_cycle).m == 1)
	{
		system("pkill -STOP afplay  &> /dev/null &");
		(*main_cycle).m = 2;
		mvwprintw(*win, (*main_cycle).winner_str + 10, 199,
			"=============> MUSIC  ON pause <==============");
		wrefresh(*win);
	}
	else
	{
		system("pkill -CONT afplay  &> /dev/null &");
		(*main_cycle).m = 1;
		mvwprintw(*win, (*main_cycle).winner_str + 10, 199,
			"=============> MUSIC  ON play <==============");
		wrefresh(*win);
	}
}

void	music_listener(char spc, t_cycle *main_cycle, WINDOW **win)
{
	if (spc == 'm')
		music_stop_pause(main_cycle, win);
	else if (spc == 'n')
	{
		system("pkill afplay &> /dev/null &");
		(*main_cycle).m = 0;
		mvwprintw(*win, (*main_cycle).winner_str + 10, 199,
			"=============> MUSIC  OFF <==============");
		wrefresh(*win);
	}
}

void	speed_listener(char spc, t_cycle *main_cycle, WINDOW **win)
{
	if (spc == 'q' || spc == 'w' || spc == 'e' || spc == 'r')
	{
		if (spc == 'q')
			(*main_cycle).second_limit -= 10;
		else if (spc == 'w')
			(*main_cycle).second_limit -= 1;
		else if (spc == 'e')
			(*main_cycle).second_limit += 1;
		else if (spc == 'r')
			(*main_cycle).second_limit += 10;
		if ((*main_cycle).second_limit <= 0)
			(*main_cycle).second_limit = 1;
		mvwprintw(*win, 4, 199, "Cycles/second limit : %d\n",
			(*main_cycle).second_limit);
		wrefresh(*win);
	}
	else
		music_listener(spc, main_cycle, win);
}

void	char_listener(t_cycle *main_cycle, WINDOW **win)
{
	char		spc;

	spc = '\0';
	spc = (char)getch();
	if (spc == ' ')
	{
		if ((*main_cycle).run == 1)
		{
			(*main_cycle).run = 0;
			mvwprintw(*win, 2, 199, "** PAUSED **\n");
			wrefresh(*win);
			nodelay(stdscr, FALSE);
		}
		else if ((*main_cycle).run == 0)
		{
			(*main_cycle).run = 1;
			mvwprintw(*win, 2, 199, "** RUNNING **");
			wrefresh(*win);
			nodelay(stdscr, TRUE);
		}
	}
	else
		speed_listener(spc, main_cycle, win);
}
