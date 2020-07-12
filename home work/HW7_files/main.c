#include "header.h"

void sig_winch(int signo) {    
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
	resizeterm(size.ws_row, size.ws_col); 
}

int main() {

	int file;
	char buff[255];
	initscr();    
	signal(SIGWINCH, sig_winch); 		
	curs_set(FALSE);
	start_color();
	refresh();
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
	draw_wind();
	wprintw(text, "Some text\n");
	wprintw(wndf, "File text");
	wrefresh(wnd);
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
