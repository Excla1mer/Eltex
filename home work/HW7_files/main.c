#include "header.h"

void sig_winch(int signo) {    
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);    
	resizeterm(size.ws_row, size.ws_col); 	
}

char open_file(char *file_name, struct winsize size) {
	int file;
	file = open(file_name, O_CREAT, O_RDWR);
	char buff[81];
	if(file == -1){
		printw("File wrong");
	}
	else {
		move(0, 0);
		for(int i = 0; i < size.ws_row - 2; i++) {
			memset(buff, 0 , 81);
			read(file, buff, 80);
			move(i, 0);
			printw("%s", buff);
		}
		move(size.ws_row - 1, 0);
		printw("file '%s' is opened! Press 'esc' to exit", file_name);
	}
	close(file);
}

/*char write_file(char *file_name, chtype *buff, int size) {
	int file;
	static int t;
	file = open(file_name, O_WRONLY);
	int chek;
	if(file == -1){
		printf("File wrong");
	}
	else {
		for(int i = 0; i < 80; i++) {
			chek = write(file, &buff[i], 1);
		}
		if(chek == -1) {
			move(10,10);
			printf("Error of input to file");
			getch();
		}
		
	}
	if(t == size)
	{
		close(file);
		t = 0;
	}
	t++;
}*/

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
	printw("                                                                                                                       \0");	
	refresh();	
	return t;
}

int main() {
	int file = 0;
	char file_name[30];
	chtype *str;
	int symb;
	int chek;
	bool ex =  false;
 	str = calloc(80, sizeof(chtype));
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
				ex = false;
				curs_set(TRUE);
				start_color();
				draw_input(file_name, size);
				open_file(file_name, size);
				int x = 0;
				int y = 0;
				move(x, y);
				cbreak();
				noecho();
  				keypad(stdscr, true);
				refresh();
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
						case 27: // Esc
							ex = true;
							break;
						case KEY_BACKSPACE:
							if(y == 0) {
								move(size.ws_row - 1, 0);
								printw("                                                                     \0");

								move(size.ws_row - 1 , size.ws_col/2);
								printw("                             \0");
								move(x, y);
								deleteln();
								x--;
								move(size.ws_row - 1, 0);
								printw("file '%s' is opened! Press 'esc' to exit", file_name);
								move(x, 80);
							}
							else {
								y--;
								move(x, y);
								delch();// функция удаляет симовол на котором стоит коретка
							}
							move(x, y);
							break;
						case 10:
							move(size.ws_row - 1, 0);
							printw("                                                                  \0");
							x++;
							move(x, 0);
							insdelln(1); // Функция сдвигает текст вниз и добовляет пустую строку
							move(size.ws_row - 1, 0);
							printw("file '%s' is opened! Press 'esc' to exit", file_name);
							move(x, y);
							break;
						default :
							insch(symb);// ввод обычных символов
							y++;
							move(x, y);
							break;
					}
					move(size.ws_row - 1 , size.ws_col/2);
					printw("                             \0");
					move(size.ws_row - 1 , size.ws_col/2);
					printw("(%d, %d)", x, y);
					move(x, y);
					refresh();
				} while( !ex );			
				break;
			case KEY_F(2):// Сохранение настроек 
				x = 0;
				y = 0;
				move(size.ws_row - 1, 0);
				printw("                                                  \0");
				file = open(file_name, O_WRONLY);
				
				if(file == -1){
					printf("File wrong");
				}
				else {
				
					for(int s = 0; s < size.ws_row - 2; s++)
					{
						mvinchnstr(s, 0, str, 79);// Считывание s строки из 79 символов в буффер str
						for(int i = 0; i < 80; i++) {
							chek = write(file, &str[i], 1);
							if(chek == -1) {
								move(10,10);
								printf("Error of input to file");
								getch();
							}
						}
					}
					close(file);
				}
				move(size.ws_row - 1, 0);
				printw("file %s saved", file_name);
				getch();
				// Очищаю экран 
				for(int i = 0; i < size.ws_row - 2; i++) {
					move(i, 0);
					printw("                                                                                               \0");
				}
				refresh();
				break;
			case KEY_F(3):
				endwin();
				free(str);
				_Exit(0);
				break;
			default :
				printw("Input error");	
				break;
		}

	}
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	return 0;
}
