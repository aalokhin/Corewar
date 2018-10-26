#include "corewar.h"

void 	map_to_screen(unsigned char *map, int indexes[MEM_SIZE][2])
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

	WINDOW * win = newwin(70, xMax-80, yMax-80, 5);
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



	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_BLUE);
	init_pair(33, COLOR_BLACK, COLOR_RED);
	init_pair(44, COLOR_BLACK, COLOR_CYAN);
	
	//indexes[1] = indexes[1]; 



	wattron(win, COLOR_PAIR(12));
	wborder(win, ls, rs, ts, bs, tl, tr, bl, br);
	mvwvline(win, 1, 196, 42, 70);
	wattroff(win, COLOR_PAIR(12));
	refresh();  


map[0] = map[0];
	 i = 0;
	 y = 2;
	 x = 3;
	
	while (i < MEM_SIZE + 1)
	{
		x = 3;
   		while (x < 192)
    	{
    		if (indexes[i][0] == 1)
    		{
    			if(indexes[i][1] == 1)
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
    		else if (indexes[i][0] == 2)
    		{
    			if(indexes[i][1] == 1)
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
    		else if (indexes[i][0] == 3)
    		{
    			if(indexes[i][1] == 1)
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
    		else if (indexes[i][0] == 4)
    		{
    			if(indexes[i][1] == 1)
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

    	y++;
	}
	wrefresh(win);
	 getch();
	endwin();
	
}