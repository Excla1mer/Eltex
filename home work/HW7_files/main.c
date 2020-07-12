#include "header.h"

void sig_winch(int signo) {    
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
	resizeterm(size.ws_row, size.ws_col); 
	
}


int main() {

	int file = -1;
	char buff[255];
	char file_name[255];
	char stat;
	initscr();    
	signal(SIGWINCH, sig_winch);
	draw_wind(0);
	wrefresh(wnd);	
	do {
		cbreak();
		curs_set(FALSE);
		delwin(text);
                text = derwin(text_r, 1, size.ws_col - 25, 1, 1);// Текст
		wprintw(text, "\n");
		
		wprintw(text, "Enter O - to open, S - to save, C - to close file");
		wrefresh(text);	
		//wgetnstr(wndf, stat, 1);
		scanf("%c", &stat);
		switch(stat) {
			case 'o':		
				delwin(text);		
				text = derwin(text_r, 1, size.ws_col - 25, 1, 1);// Текст
				delwin(subsub1);
				subsub1 = derwin(sub1wnd, 1, 5, 1, 1);
				wbkgd(subsub1, COLOR_PAIR(1));
				wprintw(subsub1 ,"Open");
				wrefresh(subsub1);
				wprintw(text, "Enter file  name :");
				nocbreak();
				wrefresh(wndf);
				wgetnstr(text, file_name, 255);
				file = open(file_name, O_RDWR | O_CREAT);
				if(file  == -1) {
					wprintw(wndf, "Error of file");
					refresh();
				}
				else {
							
					read(file, buff, sizeof(buff));
					wprintw(wndf, "%s", buff);
					wrefresh(wndf);
					move(1,1);
					curs_set(TRUE);
					do {
						wgetnstr(wndf, buff, 224);
						scanf("%c", &stat);					
					}while(stat != 'p');
				}
				delwin(subsub1);
                                subsub1 = derwin(sub1wnd, 1, 5, 1, 1);
                                wbkgd(subsub1, COLOR_PAIR(0));
                                wprintw(subsub1 ,"Open ");
                                wrefresh(subsub1);
				break;
			case 's':
				close(file);	
				delwin(subsub2);
                                subsub2 = derwin(sub2wnd, 1, 5, 1, 1);
                                wbkgd(subsub2, COLOR_PAIR(1));
                                wprintw(subsub2 ,"Save");
                                wrefresh(subsub2);
				file = open(file_name, O_WRONLY);
				if(file == -1) {
					_Exit(0);
				
				}
				else {
					write(file, stdscr, sizeof(stdscr));
					close(file);
				}
				/*delwin(subsub2);
                                subsub2 = derwin(sub2wnd, 1, 5, 1, 1);
                                wbkgd(subsub2, COLOR_PAIR(0));
                                wprintw(subsub2 ,"Save ");
                                wrefresh(subsub2);*/

				break;
			case 'c': 
				break;
			case 'e':
				break;
			default :
				break;

		
		}
	
	} while( stat != 'e');
	wprintw(text, "Some text\n");
	wprintw(wndf, "File text");
	wrefresh(wnd);
	wrefresh(wndf);
	delwin(wnd);
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	//file = open("file.txt", O_RDWR | O_CREAT);
	//printf("Enter word: ");
	//scanf("%s", &buff);
	//write(file, buff, sizeof(buff));
	//close(file);
	//file = open("file.txt", O_RDONLY);
	//read(file, buff, sizeof(buff));
	//printf("%s", buff);
	return 0;
}
