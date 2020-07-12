#include "header.h"


void draw_wind() {
	wnd = newwin(size.ws_row, size.ws_col, 0, 0); // Окно всей программы
	wndf_r = derwin(wnd, size.ws_row - 5, size.ws_col, 0, 0);// Место отображения файлов
	wndf = derwin(wndf_r, size.ws_row - 7, size.ws_col - 2, 1, 1);
	text_r = derwin(wnd, 3, size.ws_col - 23, size.ws_row - 4, 22);
	text = derwin(text_r, 1, size.ws_col - 25, 1, 1);
	sub1wnd = derwin(wnd, 3, 7, size.ws_row - 4, 1);// Рамка для Open
	subsub1 = derwin(sub1wnd, 1, 6, 1, 1);//Текст Open
	sub2wnd = derwin(wnd, 3, 7, size.ws_row - 4, 8);// Рамка для Save
	subsub2 = derwin(sub2wnd, 1, 6, 1, 1);// Текст Save
	sub3wnd = derwin(wnd, 3, 7, size.ws_row - 4, 15);// Рамка для Close
	subsub3 = derwin(sub3wnd, 1, 6, 1, 1);// Текст Close
	box(wnd,  '|', '-');
	box(wndf_r,  '|', '-');
	box(text_r,  '|', '-');
	box(sub1wnd, '|', '-');
	box(sub2wnd, '|', '-');
	box(sub3wnd, '|', '-'); 	
	wprintw(subsub1, "Open");	
	wprintw(subsub2, "Save");
	wprintw(subsub3, "Close");
}
