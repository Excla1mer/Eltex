#include "header.h"

void sig_winch(int signo) {    
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
	resizeterm(size.ws_row, size.ws_col); 	
}

char open_file(char *file_name,  int *file) {
	*file = open(file_name, O_CREAT, O_RDWR);
	char buff[255];
	if(*file == -1){
		printw("File wrong");
	}
	else {
		read(*file, buff, sizeof(buff));
		printw("file '%s' is opened!", file_name);
		move(0, 0);
		printw("%s", buff);
		move(0, 0);
	}
	close(file);
}

char write_file(char *file_name, int *file, chtype buff) {
	*file = open(file_name, O_WRONLY);
	int chek;
	if(*file == -1){
		printf("File wrong");
	}
	else {
		chek = write(*file, &buff, 79);
		if(chek == -1) {
			move(10,10);
			printw("Error of input to file");
			getch();
		}
		write(*file, "\0", 1);
		
	}

	close(*file);
}

void  draw_input(char *file_name, struct winsize size) {

	move(size.ws_row - 1, 0);
	printw("Input file name: ");	
	refresh();
	nocbreak();
	echo();
	wgetnstr(stdscr, file_name, 30);
	move(size.ws_row - 1, 0);
	printw("                                                  \0");
	move(size.ws_row - 1, 0);
}

int start_draw(struct winsize size)  {
	int t;
	cbreak;
	curs_set(FALSE);
	move(size.ws_row - 1, 0);
	printw("To open file click - f1 | To save file click - f2 | To close programm click - f3");
	move(size.ws_row - 1, 0);
	t = getch();
	printw("                                                                                   \0");	
	refresh();	
	return t;
}

int main() {
	int file = 0;
	char file_name[30];
	chtype *buff;
	int symb;
	bool ex =  false;
	initscr();
  	keypad(stdscr, true);
	while(1) {
  		signal(SIGWINCH, sig_winch);	
		curs_set(FALSE);
		start_color();
		cbreak();
		refresh();
		noecho();
		ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
		switch(start_draw(size)) {
			case KEY_F(1):

				//endwin();
				//initscr();
  				//signal(SIGWINCH, sig_winch);	
				ex = false;
				curs_set(TRUE);
				start_color();
				draw_input(file_name, size);
				open_file(file_name,  &file);
				int x = 0;
				int y = 0;
				cbreak();
				noecho();
  				keypad(stdscr, true);
				do {
					symb = getch();
					switch(symb) {
						case KEY_UP:
							if(x > 0)
								x--;
							move(x, y);
							break;
						case KEY_DOWN:
							if(x < (size.ws_row - 1))
								x++;
						       	move(x, y);	
							break;
						case KEY_LEFT:
							if(y > 0)
								y--;
							move(x, y);
							break;
						case KEY_RIGHT:
							if(y < (size.ws_col - 1))
								y++;
							move(x, y);
							break;
						case KEY_F(4):
							ex = true;
							break;
						case KEY_BACKSPACE:
							if(y == 0) {
								move(size.ws_row - 1, 0);
								printw("                                                  \0");
								move(x, y);
								deleteln();
								x--;
								move(size.ws_row - 1, 0);
								printw("file '%s' is opened!", file_name);
								move(x, y);
							}
							else {
								delch();
								y--;
							}
							move(x, y);
							break;
						case 10:
							move(size.ws_row - 1, 0);
							printw("                                                  \0");
							move(x, y);
							insdelln(1);
							x++;
							move(size.ws_row - 1, 0);
							printw("file '%s' is opened!", file_name);
							move(x, y);
							break;
						default :
							insch(symb);
							y++;
							move(x, y);
							break;
					}
					refresh();
				} while( !ex );			
				break;
			case KEY_F(2):
				x = 0;
				y = 0;
				move(size.ws_row - 1, 0);
				printw("                                                  \0");
			//	mvwinchnstr(stdscr, x, y, buff, 2);
				buff = calloc(80, sizeof(chtype));
				//mvinchnstr(0, 0, buff, 80);
				move(0,0);
				for(int i=0;i < 10;i++) {
					mvinchstr(0, i, buff[i]);
				}
				//vinnstr(0, 0, buff, 80);
				curs_set(TRUE);
				refresh;
				echo();
				//wgetnstr(stdscr, buff, 30);
				write_file(file_name, &file, buff);
				move(size.ws_row - 1, 0);
				printw("file %s saved", file_name);
				getch();
				break;
			case KEY_F(3):
				endwin();
				_Exit(0);
				break;
			default :
				printw("Input error");	
				break;
		}

	}
	//draw_input(file_name, size);
	//open_file(file_name, &file);
	//write_file(file_name, &file);
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	return 0;
}
