#include "../corewar.h"

void print_map_info(WINDOW * win, t_cycle *main_cycle, t_flags *params, t_proc *processes)
{
	int x;
	int y;
	int tmp;

	x = 199;
	y = 4;
	wrefresh(win);
	mvwprintw(win, y, x,  "Cycles/second limit : %d", (*main_cycle).second_limit);
	wrefresh(win);
	y += 3;
	mvwprintw(win, y, x,  "Cycles: %d", (*main_cycle).cycles);
	y += 2;
	mvwprintw(win, y, x,  "Processes: %d", (*main_cycle).processes);
	while ((*processes).real_id != (*params).bots_quantity - 1)
		processes = processes->next;
	
	y = y + (4 * (*params).bots_quantity);
	tmp = y;
	x+=2;
	while (processes)
	{	
		mvwprintw(win, y, x,  "Lives in current period : %d ", (*processes).lives);
		y -= 1;
		mvwprintw(win, y, x,  "Last live: %d ", (*processes).last_live_cycle);
		y -= 3;
		processes = processes->next;
	}
	y = tmp + 3;
	x-=2;
	mvwprintw(win, y, x,  "CYCLE_TO_DIE : %d", (*main_cycle).cycle_die);
	y += 2;
	mvwprintw(win, y, x,  "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	mvwprintw(win, y, x,  "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win, y, x,  "MAX_CHECKS : %d", MAX_CHECKS);
	y += 2;
	if ((*main_cycle).winner_name )
		mvwprintw(win, y, x,  "Current winner is : %s", (*main_cycle).winner_name);
	(*main_cycle).winner_str = y + 2;
	wrefresh(win);
}

void print_winner(WINDOW **win, t_cycle *main_cycle)
{
	int x;
	int y;
	char c;

	x = 199;
	y = (*main_cycle).winner_str;
	wattron(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
	mvwprintw(*win, y, x,  "The winner is : %s", (*main_cycle).winner_name);
	wattroff(*win, COLOR_PAIR((*main_cycle).winner_id + 1));
	y += 2;
	mvwprintw(*win, y, x,  "Press any key for exit");
	wrefresh(*win);
	nodelay(stdscr, FALSE);
	c = (char)getch();
	wclear(*win);
	endwin();
}

void visual_init(WINDOW **win, t_flags *params, t_header bots[MAX_PLAYERS])
{
	int  yMax;
	int  xMax;
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
	getmaxyx(stdscr, yMax, xMax);
	*win = newwin(68, 0, 0, 5);
	int ls, rs, ts, bs, tl, tr, bl, br;
	ls = rs = ts = bs = tl = tr = bl = br = 42;
	init_pair(12, COLOR_CYAN, COLOR_CYAN);
	init_pair(1 , COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5 , COLOR_WHITE, COLOR_BLACK);
	init_pair(6 , COLOR_RED, COLOR_RED);
	init_pair(7 , COLOR_CYAN, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_BLUE);
	init_pair(33, COLOR_BLACK, COLOR_RED);
	init_pair(44, COLOR_BLACK, COLOR_CYAN);
	init_pair(55, COLOR_BLACK, COLOR_WHITE);
	wattron(*win, COLOR_PAIR(12));
	wborder(*win, ls, rs, ts, bs, tl, tr, bl, br);
	mvwvline(*win, 1, 196, 42, 70);
	wattroff(*win, COLOR_PAIR(12));
	while (i < (*params).bots_quantity)
	{
		y += 2;
		mvwprintw(*win, y, x,  "Player: -%d : %s", bots[i].id + 1, bots[i].prog_name);
		i++;
		y += 2;
	}
}

void 	map_to_screen(unsigned char *map, t_cycle *main_cycle, t_flags *params, t_proc *processes, WINDOW *win)
{
	int i;
	int y;
	int x;

	i = 0;
	y = 2;
	x = 3;

	refresh();

	while (i < MEM_SIZE)
	{
		x = 3;
   		while ( x < 194)
    	{
    		if ((*main_cycle).indexes[i][0] == 1)
    		{
    			if((*main_cycle).indexes[i][1] == CARETKA)
    			{
	    			wattron(win, COLOR_PAIR(11));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(11));
    			}
    			else
    			{
	    			wattron(win, COLOR_PAIR(1));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(1));
		    	}
    		}
    		else if ((*main_cycle).indexes[i][0] == 2)
    		{
    			if((*main_cycle).indexes[i][1] == CARETKA)
    			{
	    			wattron(win, COLOR_PAIR(22));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(22));
    			}
    			else
    			{
					wattron(win, COLOR_PAIR(2));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(2));
	    		}
    		}
    		else if ((*main_cycle).indexes[i][0] == 3)
    		{
    			if((*main_cycle).indexes[i][1] == CARETKA)
    			{
	    			wattron(win, COLOR_PAIR(33));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(33));
    			}
    			else
    			{
	    			wattron(win, COLOR_PAIR(3));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(3));
		    	}
    		}
    		else if ((*main_cycle).indexes[i][0] == 4)
    		{
    			if((*main_cycle).indexes[i][1] == CARETKA)
    			{
	    			wattron(win, COLOR_PAIR(44));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(44));
    			}
    			else
    			{
	    			wattron(win, COLOR_PAIR(4));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(4));
		    	}
    		}
    		else
			{
				if((*main_cycle).indexes[i][1] == CARETKA)
    			{
	    			wattron(win, COLOR_PAIR(55));
		    		mvwprintw(win, y, x,  "%.2x", map[i]);
		    		wattroff(win, COLOR_PAIR(55));
    			}
    			else
    			{
    				wattron(win, COLOR_PAIR(5));
					mvwprintw(win, y, x,  "%.2x", map[i]);
					wattroff(win, COLOR_PAIR(5));
    			}

			}

    		x += 3;
    		i++;
    	}
    	print_map_info(win, main_cycle, params, processes);
    	//wrefresh(win);
    	y++;
	}
	//wrefresh(win);

}
