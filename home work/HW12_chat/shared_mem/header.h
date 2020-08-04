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
#include <mqueue.h>
#include <pthread.h>

#include <semaphore.h>
#include <sys/mman.h>
struct winsize size;


WINDOW* wnd_l;
WINDOW* wnd_r;
WINDOW* wnd_b;

