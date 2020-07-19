#include "header.h"

void sig_winch(int signo) {
        ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
        resizeterm(size.ws_row, size.ws_col);
}

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
        	        	wprintw(wnd_l, "%-30s", buff_l[i]->d_name);
				
			}
			else {
				wattron(wnd_l, COLOR_PAIR(1));
				wmove(wnd_l, i, 1 );
        	        	wprintw(wnd_l, "%-30s", buff_l[i]->d_name);
				
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
                                wprintw(wnd_r, "%-30s", buff_r[i]->d_name);

                        }
                        else {
                                wattron(wnd_r, COLOR_PAIR(1));
                                wmove(wnd_r, i, 1 );
                                wprintw(wnd_r, "%-30s", buff_r[i]->d_name);

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
int main() {
	struct dirent **buff_l;
	struct dirent **buff_r;
	int l, r;
	int symb;
	int x, y;
	pid_t pid;
	char *path_l;
	//char *path_r;
	char path_r[255] = "/";
	path_l = getenv("PWD");
	//path_r = getenv("PWD");
	l = scandir(path_l, &buff_l, NULL, alphasort);
	r = scandir(path_r, &buff_r, NULL, alphasort);
	initscr();
	keypad(stdscr, true);
	keypad(wnd_r, true);
	keypad(wnd_l, true);
	signal(SIGWINCH, sig_winch);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_GREEN);
        init_pair(2, COLOR_YELLOW, COLOR_BLUE);
	x = 1;
	y = 0;
	while(1) {
		curs_set(FALSE);
		cbreak();
		noecho();
		ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
		boxes(size, path_l, path_r);
		print_dirs(buff_l, l, buff_r, r, x, y);
		symb = getch();
		switch(symb) {
			case KEY_UP:
				if(x > 1)
					x--;
				break;
			case KEY_DOWN:
				x++;
				break;
			case KEY_BTAB:
				if(y == 0) 	y++;
				else 		y  = 0;
				x = 1;
				break;
			case 10:
				if(y == 0) {
					int chek;
					int len = strlen(path_l);
					chek = strcmp(buff_l[x]->d_name, "..");
					if(chek == 0) {
						for(int i = len; i >= 0; i--) {
							if(path_l[i] == '/') {
								path_l[i] = '\0';
								break;
							}
						}
					}
					else {
						strncat(path_l,  "/", 1);
				    		strncat(path_l, buff_l[x]->d_name,  50);	
					}
					l = scandir(path_l, &buff_l, NULL, alphasort);
					if(l == -1) {
						pid = fork();
						if(pid == 0){
							delwin(wnd_l);
							delwin(wnd_r);
							endwin();
							system("clear");
							execl(path_l, NULL);
							getch();
							return 0;
						}
						else {
							wait(NULL);
							initscr();
							signal(SIGWINCH, sig_winch);
        						start_color();
        						curs_set(FALSE);
							boxes(size, path_l, path_r);
							print_dirs(buff_l, l, buff_r, r, x, y);
							keypad(stdscr, true);
       						keypad(wnd_r, true);
        						keypad(wnd_l, true);
        						refresh();
							wrefresh(wnd_l);
							wrefresh(wnd_r);
							len = strlen(path_l);
							for(int i = len; i >= 0; i--) {
                                                        	if(path_l[i] == '/') {
                                                                	path_l[i] = '\0';
                                                               	 	break;
                                                        	}
                                                	}
							l = scandir(path_l, &buff_l, NULL, alphasort);

						}
					
					}

				}
				else {
					int chek;
                                        int len = strlen(path_r);
                                        chek = strcmp(buff_r[x]->d_name, "..");
                                        if(chek == 0) {
                                                for(int i = len; i >= 0; i--) {
                                                        if(path_r[i] == '/') {
                                                                path_r[i] = '\0';
                                                                break;
                                                        }
                                                }
                                        }
                                        else {
                                                strncat(path_r,  "/", 1);
                                                strncat(path_r, buff_r[x]->d_name,  50);
                                        }
                                        r = scandir(path_r, &buff_r, NULL, alphasort);
                                        if(r == -1) {
						pid = fork();
						if(pid == 0){
							delwin(wnd_r);
							delwin(wnd_l);
							endwin();
							system("clear");
							execl(path_r, NULL);
							getch();
							return 0;
						}
						else {
							wait(NULL);
							initscr();
							signal(SIGWINCH, sig_winch);
        						start_color();
        						curs_set(FALSE);
							boxes(size, path_l, path_r);
							print_dirs(buff_l, l, buff_r, r, x, y);
							keypad(stdscr, true);
       						keypad(wnd_r, true);
        						keypad(wnd_l, true);
        						refresh();
							wrefresh(wnd_l);
							wrefresh(wnd_r);
							len = strlen(path_r);
							for(int i = len; i >= 0; i--) {
                                                        	if(path_r[i] == '/') {
                                                                	path_r[i] = '\0';
                                                               	 	break;
                                                        	}
                                                	}
							r = scandir(path_r, &buff_r, NULL, alphasort);

						}
					
					}


				
				}
				refresh();
				wrefresh(wnd_l);
				wrefresh(wnd_r);
				x = 1;
				break;
			case  27:
				echo();
				system("clear");
				curs_set(TRUE);
				nocbreak;
				free(buff_r);
				free(buff_l);
				_Exit(0);
		}

			refresh();
			wrefresh(wnd_l);
			wrefresh(wnd_r);


	}
	return 0;

}
