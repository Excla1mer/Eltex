#include "header.h"

#define NAME_SIGN "/signals01"
#define NAME_MSG "/messages1"
#define MAX_MSG 10
#define MAX_MSG_SIZE 80

unsigned int count_u; // count of users
unsigned int count_m; // count of messages 

mqd_t client[10];
void* signals(void *param) {
	
	mqd_t sign;
	char** users = (char **)param;
	struct mq_attr attr;
	char client_ch[80] = "/";
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MSG;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	if((sign = mq_open(NAME_SIGN, O_RDONLY | O_CREAT, 0777, &attr)) == -1) {
		perror("SIGN mq_open:");
		exit(1);
	}
	users[0] = malloc(80);
	while(1) {
		if(mq_receive(sign, users[count_u], attr.mq_msgsize, NULL) == -1) {
			perror("SIGN mq_receive");
                        exit(1);
                }
		//client[count_u] = malloc(sizeof(mqd_t));
                strcat(client_ch, users[count_u]);
		users[count_u] = malloc(80);
		if((client[count_u] = mq_open(client_ch, O_WRONLY | O_CREAT, 0777, &attr)) == -1) {
                	perror("SIGN mq_open:");
                	exit(1);
        	}

		/*for(int i = 0; i < count; i++){
			if(mq_send(client_ch, users[i], attr.mq_msgsize, NULL) == -1) {
                        	perror("SIGN mq_receive");
                        	exit(1);
                	}

		}*/
		count_u++;
	}

}

int main()  {
	mqd_t msg;
	char client_ch[80] = "/";
	char** u_names = malloc(sizeof(char*));
	char** msg_buff = malloc(sizeof(char*));
	pthread_t tid_sign;
	struct mq_attr attr;
	msg_buff[count_m] = malloc(80);
    	attr.mq_flags = 0;
    	attr.mq_maxmsg = MAX_MSG;
    	attr.mq_msgsize = MAX_MSG_SIZE;
    	attr.mq_curmsgs = 0;
	//msg = mq_open(NAME_MSG, O_RDWR | O_CREAT, 0777, NULL);
	if((msg = mq_open(NAME_MSG, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
                perror("MSG mq_open:");
                exit(1);
        }
	pthread_create(&tid_sign, NULL, signals, u_names);
	while(1) {
		if(mq_receive(msg, msg_buff[count_m], attr.mq_msgsize, NULL) == -1) {
			perror("MSG mq_receive");
			exit(1);
		} else count_m++;

		for(int i = 0; i < count_u; i++) {
			if(mq_send(client[i], msg_buff[count_m-1], attr.mq_msgsize, 0) == -1) {
                                perror("SIGN mq_receive");
                                exit(1);
                        }
			/*memset(client_ch, 0, sizeof(client_ch));
			strcat(client_ch, "/");*/
		}
	}
	return 0;
}
