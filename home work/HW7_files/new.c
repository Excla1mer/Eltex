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

char write_file(char *file_name, int *file) {
	*file = open(file_name, O_WRONLY);
	char buff[255];
	int chek;
	if(*file == -1){
		printf("File wrong");
	}
	else {
		printf("Input to file: ");
		scanf("%s", buff);
		buff[255]  =  0;
		chek = write(*file, buff, sizeof(buff));
		if(chek == -1) {
			printf("Error of input to file");
		}
	}

	close(*file);
}

void  draw_input(char *file_name, struct winsize size) {

	move(size.ws_row - 1, 0);
	printw("Input file name: ");	
	refresh();
	nocbreak();
	wgetnstr(stdscr, file_name, 30);
	move(size.ws_row - 1, 0);
	printw("                                                  \0");
	move(size.ws_row - 1, 0);
}

int start_draw(struct winsize size)  {
	int t;
	cbreak;
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
	int symb;
	bool ex =  false;
	initscr();
  	keypad(stdscr, true);
  	signal(SIGWINCH, sig_winch);	
	curs_set(FALSE);
	start_color();
	refresh();
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	while(1) {
		switch(start_draw(size)) {
			case KEY_F(1):
				draw_input(file_name, size);
				open_file(file_name,  &file);
				int x = 0;
				int y = 0;
				curs_set(TRUE);
				nocbreak;
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
							if(x < 50)
								x++;
							y++;
						       	move(x, y);	
							break;
						case KEY_LEFT:
							if(y > 0)
								y--;
							move(x, y);
							break;
						case KEY_RIGHT:
							if(y < 50)
								y++;
							break;
						case KEY_F(4):
							ex = true;
							break;
						default :
							/*printw("%c", symb);
							y++;
							move(x, y);*/
							break;
					}
					refresh();
				} while( !ex );			
				break;
			case KEY_F(2):
				printw("22222222222222222222222");
				break;
		
		}
	
	}
	draw_input(file_name, size);
	open_file(file_name, &file);
	//write_file(file_name, &file);
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	return 0;
}
