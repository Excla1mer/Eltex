#include "header.h"


void boxes(struct winsize size, char *path_l, char *path_r) {
        wnd_l = newwin(size.ws_row, size.ws_col / 2, 0, 0);
        wnd_r = newwin(size.ws_row, size.ws_col / 2, 0, (size.ws_col / 2));
        box(wnd_l, '|', '-');
        box(wnd_r, '|', '-');
        wmove(wnd_l ,0, 2);
        wprintw(wnd_l,"%s", path_l);
        wmove(wnd_r ,0, 2);
        wprintw(wnd_r,"%s", path_r);
        refresh();
        wrefresh(wnd_l);
        wrefresh(wnd_r);
}


void print_dirs(struct dirent **buff_l, int l,struct dirent **buff_r, int r, int x, int y) {
	if(y  == 0)
	{
		for(int i  = 1; i < l; i++) {
			if(i == x)
			{
				wattron(wnd_l, COLOR_PAIR(2));
				wmove(wnd_l, i, 1 );
        	        	wprintw(wnd_l, "%-50s", buff_l[i]->d_name);
				
			}
			else {
				wattron(wnd_l, COLOR_PAIR(1));
				wmove(wnd_l, i, 1 );
        	        	wprintw(wnd_l, "%-50s", buff_l[i]->d_name);
				
			}
		}
		for(int i  = 1; i < r; i++) {
			wmove(wnd_r, i, 1 );
        	        wprintw(wnd_r, "%s", buff_r[i]->d_name);
		}
	}
	else {
		for(int i  = 1; i < r; i++) {
                        if(i == x)
                        {
                                wattron(wnd_r, COLOR_PAIR(2));
                                wmove(wnd_r, i, 1 );
                                wprintw(wnd_r, "%-50s", buff_r[i]->d_name);

                        }
                        else {
                                wattron(wnd_r, COLOR_PAIR(1));
                                wmove(wnd_r, i, 1 );
                                wprintw(wnd_r, "%-50s", buff_r[i]->d_name);

                        }
                }

		for(int i  = 1; i < l; i++) {
			wmove(wnd_l, i, 1 );
        	        wprintw(wnd_l, "%s", buff_l[i]->d_name);
		}
	}
	refresh();
	wrefresh(wnd_l);
	wrefresh(wnd_r);

}

void *dr_copy(void *param) {
	long long *wr_file;
	wr_file = (long long *)param;
	wnd_c = newwin(4, 54, size.ws_row - 5, size.ws_row / 1.1);
	box(wnd_c, '|', '-');
	wattron(wnd_c, COLOR_PAIR(3));
	wmove(wnd_c, 2, 1);
	wprintw(wnd_c,  "[");
	wmove(wnd_c, 2, 52);
	wprintw(wnd_c,  "]");
	int x = 2;
	int y = 2;
	float  t = 0.02;
	
	while(1) {
		wmove(wnd_c, 1 , 25);
		wprintw(wnd_c,"%0.2f%%", (*wr_file*1.0)/(file_size*1.0) * 100);
		wmove(wnd_c, x, y);
		if((*wr_file*1.0)/(file_size*1.0) >= t) {
			wprintw(wnd_c,  "#");
			delch();
			t = t + 0.02;
			y++;
			
		}
		if( *wr_file == file_size) {
			wmove(wnd_c, 1, 25);	
			wprintw(wnd_c, "  DONE  ");
			refresh();
			wrefresh(wnd_l);
			wrefresh(wnd_r);
			wrefresh(wnd_c);
			getch();
			break;	
		}
		refresh();
		wrefresh(wnd_l);
		wrefresh(wnd_r);
		wrefresh(wnd_c);
		usleep(1000);
	}
}


