#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
// ***libs for ncurses work***
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
// ***libs*for*processes******
// #include <stdio.h>
// #include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>  
// ***************************
struct winsize size;

void print_dirs(struct dirent **buff_l, int l,struct dirent **buff_r, int r, int x, int y);
void boxes(struct winsize size, char *path_l, char *path_r);

WINDOW* wnd_l;
WINDOW* wnd_r;


#endif
