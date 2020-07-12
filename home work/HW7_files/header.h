#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <termios.h> 
#include <sys/ioctl.h> 
#include <signal.h> 
#include <stdlib.h> 
#include <curses.h> 

void draw_wind(int x);

struct winsize size; 



WINDOW * wnd;    
WINDOW * sub1wnd;    
WINDOW * subsub1;
WINDOW * sub2wnd;
WINDOW * subsub2;
WINDOW * sub3wnd;
WINDOW * subsub3;
WINDOW * wndd_r;
WINDOW * wndd;
WINDOW * wndf_r;
WINDOW * wndf;
WINDOW * text_r;
WINDOW * text;


#endif
