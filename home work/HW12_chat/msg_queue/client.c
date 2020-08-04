#include "header.h"

#define NAME_SINC_MSG "/sinc-msg"
#define NAME_SIGN "/signals11"
#define NAME_MSG "/messages11"
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

unsigned int count_u; // количество юзеров в чате 
unsigned int count_m; // количество сообщений в чате

void box_users(struct winsize size, char u_names[20][80]);
void box_msg(struct winsize size, char msg_buff[100][81], char sender[100][80]);
void box_input(struct winsize size);

struct mq_attr attr = {0, MAX_MSG, MAX_MSG_SIZE, 0};

mqd_t client;


/* Функция clients_msg ждет послупдения сообщеий в личный канал client.
   При получении сообщения записывает его в буффер сообщений msg_buff */
void* clients_msg(void *param);


int main(int argc, char *argv[]) {
	mqd_t sinc_msg;
	mqd_t msg;
	mqd_t sign;
	struct new st;
	char msg_b[80] = "123";
	char  client_ch[80] = "/";
	pthread_t tid_msg;
	strcat(client_ch, argv[1]);
	//printf("%s\n", client_ch);
	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    init_pair(3, COLOR_RED, COLOR_BLUE);
	signal(SIGWINCH, sig_winch);
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	if((client = mq_open(client_ch, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
        perror("client mq_open:");
        exit(1);
   	} 	
	if((msg = mq_open(NAME_MSG, O_RDWR)) == -1) {
        perror("MSG mq_open:");
        exit(1);
    }
    //printf("open msg\n");	
	if((sign = mq_open(NAME_SIGN, O_RDWR)) == -1) {
        perror("SIGN mq_open:");
        exit(1);
    }
    //printf("open sign\n");
	if(mq_send(sign, argv[1], strlen(argv[1]) + 1, 0) == -1) {
		perror("SIGN mq_send");
		exit(1);
	}
	//printf("sended sign\n");
	/* Цикл отвечающий за синхронизацию сообщений */
	while(1) {
		if(mq_receive(client, st.msg_buff[count_m], attr.mq_msgsize, 0) == -1) {
         	perror("Client mq_receive");
        	exit(1);
    	} else count_m++;
    	//printf("%s\n", st.msg_buff[count_m-1]);
    	if(strcmp(st.msg_buff[count_m-1], "end-sinc-msg") == 0) {
    		count_m--;
    		break;
    	}
	}
	int tmp = 0;
	/* Цикл отвечающий за синхронизацию отправителей сообщений */
	while(1) {
		if(mq_receive(client, st.sender[tmp], attr.mq_msgsize, 0) == -1) {
         	perror("Client mq_receive");
        	exit(1);
    	}
    	if(strcmp(st.sender[tmp], "end-sinc-sender") == 0) {
    		tmp--;
    		break;
    	}
    	tmp++;
	}
	/* Цикл отвечающий за синхронизацию имен юзеров чата */
	while(1) {
		if(mq_receive(client, st.u_names[count_u], attr.mq_msgsize, 0) == -1) {
         	perror("Client mq_receive");
        	exit(1);
    	}
    	count_u++;
    	if(strcmp(st.u_names[count_u-1], "end-sinc-name") == 0) {
    		count_u--;
    		break;
    	}
    	
	}
	pthread_create(&tid_msg, NULL, clients_msg, &st);
	sleep(1);
	while(1) {
		wmove(wnd_b, 1, 1);
		refresh();
	    wrefresh(wnd_l);
	    wrefresh(wnd_r);
	    wrefresh(wnd_b);
		wgetnstr(wnd_b, msg_b, 80);

		if(mq_send(msg, msg_b, strlen(msg_b) + 1, 0) == -1) {
            perror("Msg mq_send");
            exit(1);
        }
        if(mq_send(msg, client_ch, strlen(client_ch) + 1, 0) == -1) {
            perror("sender mq_send");
            exit(1);
        }

	}

	return 0;
}

void* clients_msg(void *param) {
	struct new *st;
	st = (struct new*)param;
	while(1) {
		if(mq_receive(client, st->msg_buff[count_m], MAX_MSG_SIZE, 0) == -1) {
            perror("Client mq_receive");
            exit(1);
		} else count_m++;
		if(strcmp(st->msg_buff[count_m-1], "new-user") == 0) {
			count_m--;
			if(mq_receive(client, st->u_names[count_u], MAX_MSG_SIZE, 0) == -1) {
	            perror("Client mq_receive");
	            exit(1);
			}
			count_u++;
		}
		else {
			if(mq_receive(client, st->sender[count_m-1], MAX_MSG_SIZE, 0) == -1) {
	            perror("Client mq_receive");
	            exit(1);
       		}
		}
       	box_msg(size, st->msg_buff, st->sender);
		box_users(size, st->u_names);
		box_input(size);
		refresh();
	    wrefresh(wnd_l);
	    wrefresh(wnd_r);
	    wrefresh(wnd_b);
		//printf("Got: %s\n", st->msg_buff[count_m-1]);
	}
}

void box_msg(struct winsize size, char msg_buff[100][81], char sender[100][80]) {
    wnd_r = newwin(size.ws_row - 3, size.ws_col - (size.ws_col / 4), 0, (size.ws_col / 4));
    box(wnd_r, '|', '-');
    for(int i = 0; i < count_m; i++) {
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
    for(int i = 0; i < count_u; i++) {
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