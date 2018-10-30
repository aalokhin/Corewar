#include "corewar.h"

void print_map_info(WINDOW * win, t_cycle main_cycle, t_flags *params, t_proc *processes)
{
	unsigned int i;
	int x;
	int y;

	i = 0;
	x = 199;
	y = 2;
	mvwprintw(win, y, x,  "** PAUSED **");
	y += 2;
	mvwprintw(win, y, x,  "Cycles/second limit : %d", main_cycle.second_limit);
	y += 3;
	mvwprintw(win, y, x,  "Cycles: %d", main_cycle.cycles);
	y += 2;
	mvwprintw(win, y, x,  "Processes: %d", main_cycle.processes);
	while (i < (*params).bots_quantity)
	{
		y += 2;
		mvwprintw(win, y, x,  "Player: -%d : ", (*processes).id + 1);
		x+=2;
		y++;
		mvwprintw(win, y, x,  "Last live: %d ", (*processes).last_live_cycle);
		y++;
		mvwprintw(win, y, x,  "Lives in current period : %d ", (*processes).child_proc_lives);
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
	mvwprintw(win, y, x,  "CYCLE_TO_DIE : %d", main_cycle.cycle_die);
	y += 2;
	mvwprintw(win, y, x,  "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win, y, x,  "MAX_CHECKS : %d", MAX_CHECKS);
}

void 	map_to_screen(unsigned char *map, t_cycle *main_cycle, t_flags *params, t_proc *processes)
{
	int i = 0;
	int y = 2;
	int x = 3;

	initscr();
	cbreak();
	noecho();
	start_color();

	int  yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * win = newwin(69, xMax-100, yMax-80, 5); //*newwin(int nlines, int ncols, int begin_y, int begin_x);
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
	


	wattron(win, COLOR_PAIR(12));
	wborder(win, ls, rs, ts, bs, tl, tr, bl, br);
	mvwvline(win, 1, 196, 42, 70);
	wattroff(win, COLOR_PAIR(12));
	refresh();  


	 i = 0;
	 y = 2;
	 x = 3;
	
	while (i < MEM_SIZE + 1)
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
				wattron(win, COLOR_PAIR(5));
				mvwprintw(win, y, x,  "%.2x", map[i]);
				wattroff(win, COLOR_PAIR(5));
			}

    		x += 3;
    		i++;
    	}
    	print_map_info(win, *main_cycle, params, processes);
    	y++;
	}
	
	
	

	
	wrefresh(win);
	 getch();
	endwin();
	
}