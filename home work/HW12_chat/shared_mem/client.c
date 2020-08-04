#include "header.h"

#define SHARED_MEM "/shared_mem"
#define COUNT_U "/count_u"
#define COUNT_M "/count_m"
#define MAX_MSG 10
#define MAX_MSG_SIZE 128

void sig_winch(int signo) {
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}
/* Структура хранящая в себе сообщения и имена всех пользователей чата */ 
struct new {
	char u_names[20][80];
	char msg_buff[100][81];
	char sender[100][80];
};
sem_t *count_u;
sem_t *count_m;
int users;
int messages;
void box_users(struct winsize size, char u_names[20][80]);
void box_msg(struct winsize size, char msg_buff[100][81], char sender[100][80]);
void box_input(struct winsize size);


int main(int argc, char *argv[]) {
	mqd_t sinc_msg;
	mqd_t msg;
	mqd_t sign;
	struct new *st;
	char msg_b[80] = "123";
	char  client_ch[80];
	strcpy(client_ch, argv[1]);
	
    int shm_fd;


    if((shm_fd = shm_open(SHARED_MEM, O_RDWR, 0777)) == -1) {
        perror("shm_open");
        exit(1);
    }
    if((st = (struct new*)mmap(NULL, sizeof(st), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0)) == -1) {
        perror("mmap");
        exit(1);
    } 
    if((count_u = sem_open(COUNT_U, O_EXCL)) == -1) {
        perror("sem_open count_u");
        exit(1);
    }
    if((count_m = sem_open(COUNT_M, O_EXCL)) == -1) {
        perror("sem_open count_m");
        exit(1);
    }
    sem_getvalue(count_u, &users);
    strcpy(st->u_names[users], argv[1]);
    sem_post(count_u);
	//printf("%s\n", client_ch);
	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    init_pair(3, COLOR_RED, COLOR_BLUE);
	signal(SIGWINCH, sig_winch);
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	
	//pthread_create(&tid_msg, NULL, clients_msg, &st);
	sleep(1);
	while(1) {
		wmove(wnd_b, 1, 1);
		box_msg(size, st->msg_buff, st->sender);
		box_users(size, st->u_names);
		box_input(size);
		refresh();
	    wrefresh(wnd_l);
	    wrefresh(wnd_r);
	    wrefresh(wnd_b);
		wgetnstr(wnd_b, msg_b, 80);
		refresh();
	    wrefresh(wnd_l);
	    wrefresh(wnd_r);
	    wrefresh(wnd_b);
		sem_getvalue(count_m, &messages);
		strcpy(st->msg_buff[messages], msg_b);
		strcpy(st->sender[messages], client_ch);
		sem_post(count_m);
	}

	return 0;
}


void box_msg(struct winsize size, char msg_buff[100][81], char sender[100][80]) {
    wnd_r = newwin(size.ws_row - 3, size.ws_col - (size.ws_col / 4), 0, (size.ws_col / 4));
    box(wnd_r, '|', '-');
    sem_getvalue(count_m, &messages);
    for(int i = 0; i < messages; i++) {
    	wmove(wnd_r , i+1 , 1);
    	wprintw(wnd_r,"%s:%s", sender[i], msg_buff[i]);
    }
    /*refresh();
    wrefresh(wnd_l);
    wrefresh(wnd_r);
    wrefresh(wnd_b);*/
}

void box_users(struct winsize size, char u_names[20][80]) {
    wnd_l = newwin(size.ws_row - 3, size.ws_col / 4, 0, 0);
    box(wnd_l, '|', '-');
    sem_getvalue(count_u, &users);
    for(int i = 0; i < users; i++) {
    	wmove(wnd_l , i+1, 1);
    	wprintw(wnd_l,"%s", u_names[i]);
    }
    /*refresh();
    wrefresh(wnd_l);
    wrefresh(wnd_r);
    wrefresh(wnd_b);*/
}

void box_input(struct winsize size) {
	wnd_b = newwin(3, size.ws_col, size.ws_row - 3, 0);
	box(wnd_b, '|', '-');
	/*refresh();
    wrefresh(wnd_l);
    wrefresh(wnd_r);
    wrefresh(wnd_b);*/
}