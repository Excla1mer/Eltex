#include "header.h"

#define NAME_SINC_MSG "/sinc-msg"
#define NAME_SIGN "/signals0"
#define NAME_MSG "/messages2"
#define MAX_MSG 10
#define MAX_MSG_SIZE 8192

unsigned int count_u; // количество юзеров в чате 
unsigned int count_m; // количество сообщений в чате


mqd_t client;

void* clients_msg(void *param) {
	char **msg_buff = (char **)param;
	while(1) {
		
		printf("wait msg:\n");
		if(mq_receive(client, msg_buff[count_m], MAX_MSG_SIZE, NULL) == -1) {
                        perror("Client mq_receive");
                        exit(1);
       	} else count_m++;
       	msg_buff[count_m] = malloc(80);
		printf("Got: %s\n", msg_buff[count_m-1]);
	}
}

int main(int argc, char *argv[]) {
	mqd_t sinc_msg;
	mqd_t msg;
	mqd_t sign;
	struct mq_attr attr;
	struct mq_attr attr1;
	char** msg_buff = malloc(sizeof(char*) * 10);
	char msg_b[80];
	char  client_ch[80] = "/";
	pthread_t tid_msg;
	strcat(client_ch, argv[1]);
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MSG;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	if((client = mq_open(client_ch, O_RDWR | O_CREAT, 0777, 0)) == -1) {
                perror("client mq_open:");
                exit(1);
   	} 	
	if((msg = mq_open(NAME_MSG, O_RDWR)) == -1) {
                perror("MSG mq_open:");
                exit(1);
        }
        printf("open msg\n");	
	if((sign = mq_open(NAME_SIGN, O_RDWR)) == -1) {
                perror("SIGN mq_open:");
                exit(1);
        }
        printf("open sign\n");
	if(mq_send(sign, argv[1], strlen(argv[1]) + 1, 0) == -1) {
		perror("SIGN mq_send");
		exit(1);
	}
	printf("sended sign\n");
	while(1) {
		msg_buff[count_m] = malloc(80);
		
		if(mq_receive(client, msg_buff[count_m], attr.mq_msgsize, 0) == -1) {
         	perror("Client mq_receive");
        	exit(1);
    	} else count_m++;
    	printf("%s\n", msg_buff[count_m-1]);
    	if(strcmp(msg_buff[count_m-1], "end-sinc-msg") == 0) {
    		count_m--;
    		break;
    	}
	}
	printf("**********list of msg************\n");
	for(int i = 0; i < count_m; i++) {
		printf("[%d] %s\n", i, msg_buff[i]);
	}
	printf("*********************************\n");
	//pthread_create(&tid_msg, NULL, clients_msg, msg_buff);
	while(1) {
		printf("input  msg: ");
		fgets(msg_b, 75, stdin);
		if(mq_send(msg, msg_b, strlen(msg_b) + 1, 0) == -1) {
                	perror("SIGN mq_send");
                	exit(1);
        }
	}

	return 0;
}
