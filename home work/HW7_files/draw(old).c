#include "header.h"


void draw_wind(int x) {
	
		curs_set(FALSE);
		start_color();
		refresh();
		ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
		init_pair(1, COLOR_BLUE, COLOR_GREEN);    
		init_pair(2, COLOR_YELLOW, COLOR_BLUE); 
		wnd = newwin(size.ws_row, size.ws_col, 0, 0); // Окно всей программы
		wndf_r = derwin(wnd, size.ws_row - 5, size.ws_col, 0, 0);// Рамка для отображения файлов
		wndf = derwin(wndf_r, size.ws_row - 7, size.ws_col - 2, 1, 1);//  Место для отображения 
		wndd_r = derwin(wnd, 5, size.ws_col, size.ws_row - 5, 0);
		wndd = derwin(wndd_r, 3, size.ws_col - 2, 1, 1);
		text_r = derwin(wndd, 3, size.ws_col - 23, 0, 21); // Рамка для текста
		text = derwin(text_r, 1, size.ws_col - 25, 1, 1);// Текст
		sub1wnd = derwin(wndd, 3, 7, 0, 0);// Рамка для Open
		subsub1 = derwin(sub1wnd, 1, 6, 1, 1);//Текст Open
		sub2wnd = derwin(wndd, 3, 7, 0, 7);// Рамка для Save
		subsub2 = derwin(sub2wnd, 1, 6, 1, 1);// Текст Save
		sub3wnd = derwin(wndd, 3, 7, 0, 14);// Рамка для Close
		subsub3 = derwin(sub3wnd, 1, 6, 1, 1);// Текст Close
		wattron(wndd_r, COLOR_PAIR(2));
		wattron(wndf_r, COLOR_PAIR(2));
		box(wnd,     '|', '-');
		box(wndf_r,  '|', '-');
		box(text_r,  '|', '-');
		box(wndd_r,  '|', '-');
		box(sub1wnd, '|', '-');
		box(sub2wnd, '|', '-');
		box(sub3wnd, '|', '-'); 	
		wprintw(subsub1, "Open");	
		wprintw(subsub2, "Save");
		wprintw(subsub3, "Close");
		refresh();
	
	/*delwin(wnd);
	delwin(wndf_r);
	delwin(wndf);
	delwin(wndd_r);
	delwin(wndd);
	delwin(text_r);
	delwin(text);
	delwin(sub1wnd);
	delwin(subsub1);
	delwin(sub2wnd);
	delwin(sub3wnd);
	delwin(subsub2);
	delwin(subsub3);*/
}
