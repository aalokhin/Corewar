#include "../corewar.h"

void print_map_info(WINDOW * win, t_cycle *main_cycle, t_flags *params, t_proc *processes)
{
	unsigned int i;
	int x;
	int y;

	i = 0;
	x = 199;
	y = 2;


	// if ((*main_cycle).run == 0)
		// mvwprintw(win, y, x,  "** PAUSED **");
	// else
	// 	mvwprintw(win, y, x,  "** RUNNING **");
	y += 2;
	wrefresh(win);
	mvwprintw(win, y, x,  "Cycles/second limit : %d", (*main_cycle).second_limit);
	wrefresh(win);
	y += 3;
	mvwprintw(win, y, x,  "Cycles: %d", (*main_cycle).cycles);
	y += 2;
	mvwprintw(win, y, x,  "Processes: %d", (*main_cycle).processes);
	while ((*processes).real_id != (*params).bots_quantity - 1)
		processes = processes->next;
	while (processes)
	{
		y += 2;
		mvwprintw(win, y, x,  "Player: -%d : %s", (*processes).real_id + 1, (*processes).name);
		x+=2;
		y++;
		mvwprintw(win, y, x,  "Last live: %d ", (*processes).last_live_cycle);
		y++;
		mvwprintw(win, y, x,  "Lives in current period : %d ", (*processes).live_cycle);
		processes = processes->next;
		i++;
	}
	y += 2;
	x-=2;
	mvwprintw(win, y, x,  "Live breakdown for current period :");
	y += 2;
	wattron(win, COLOR_PAIR(7));
	mvwprintw(win, y, x,  "[--------------------------------------------------]");
	wattroff(win, COLOR_PAIR(7));
	y += 2;
	mvwprintw(win, y, x,  "Live breakdown for last period :");
	y += 2;
	mvwprintw(win, y, x,  "Live breakdown for last period :");
	wattron(win, COLOR_PAIR(7));
	mvwprintw(win, y, x,  "[--------------------------------------------------]");
	wattroff(win, COLOR_PAIR(7));
	y += 2;
	mvwprintw(win, y, x,  "CYCLE_TO_DIE : %d", (*main_cycle).cycle_die);
	y += 2;
	mvwprintw(win, y, x,  "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	mvwprintw(win, y, x,  "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win, y, x,  "MAX_CHECKS : %d", MAX_CHECKS);
	(*main_cycle).winner_str = y + 2;
	wrefresh(win);
}

void print_winner(WINDOW * win, t_cycle main_cycle)
{
	int x;
	int y;

	x = 199;
	y = main_cycle.winner_str;
	wattron(win, COLOR_PAIR(main_cycle.winner_id + 1));
	mvwprintw(win, y, x,  "The winner is : %s", main_cycle.winner_name);
	wattroff(win, COLOR_PAIR(main_cycle.winner_id + 1));
	wrefresh(win);
	//getch();
}

void visual_init(WINDOW **win)
{
	initscr();
	cbreak();
	noecho();
	start_color();

	int  yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	*win = newwin(68, 0, 0, 5); //*newwin(int nlines, int ncols, int begin_y, int begin_x);
	// box(win, 0, 0);

	// int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);
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
    			if((*main_cycle).indexes[i][1] == 1)
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
    			if((*main_cycle).indexes[i][1] == 1)
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
    			if((*main_cycle).indexes[i][1] == 1)
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
    			if((*main_cycle).indexes[i][1] == 1)
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
				if((*main_cycle).indexes[i][1] == 1)
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
    	wrefresh(win);
    	y++;
	}
	wrefresh(win);

}
