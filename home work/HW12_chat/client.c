#include "header.h"

#define NAME_SIGN "/signals0"
#define NAME_MSG "/messages1"

unsigned int count_u;
unsigned int count_m;

unsigned int sgn_prio_send = 2;
unsigned int sgn_prio_receive = 1;
mqd_t client;
void* clients_msg(void *param) {
	char **msg_buff = (char **)param;
	while(1) {
		msg_buff[count_m] = malloc(80);
		printf("wait msg:\n");
		if(mq_receive(client, msg_buff[count_m], 80, NULL) == -1) {
                        perror("MSG mq_receive");
                        exit(1);
                } else count_m++;
		printf("Got: %s\n", msg_buff[count_m-1]);
		msg_buff[count_m] = malloc(80);
	}
}

int main(int argc, char *argv[]) {

	mqd_t msg;
	mqd_t sign;
	//mqd_t client;
	char** msg_buff = malloc(sizeof(char*));
	char msg_b[80];
	char  client_ch[80] = "/";
	pthread_t tid_msg;
	//msg_buff[count_m] = malloc(80);
	strcat(client_ch, argv[1]);
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
	if(mq_send(sign, argv[1], strlen(argv[1]) + 1, sgn_prio_send) == -1) {
		perror("SIGN mq_send");
		exit(1);
	}
	printf("sended sign\n");
	if(mq_receive(sign, msg_b, 80, &sgn_prio_receive) == -1) {
                        perror("SIGN mq_receive");
                        exit(1);
    	}
    	printf("got sign %s\n", msg_b);
    	if(strcmp(msg_b, argv[1]) != 0) {
    		perror("Strcmp :");
    		exit(1);
    	} 
	//sleep(1);
	if((client = mq_open(client_ch, O_RDWR)) == -1) {
                perror("client mq_open:");
                exit(1);
        }
	pthread_create(&tid_msg, NULL, clients_msg, msg_buff);
	while(1) {
		printf("input  msg: ");
		fgets(msg_b, 80, stdin);
		if(mq_send(msg, msg_b, strlen(msg_b) + 1, 0) == -1) {
                	perror("SIGN mq_send");
                	exit(1);
        	}
		/*if(mq_receive(client, msg_buff[count_m], 80, NULL) == -1) {
                        perror("MSG mq_receive");
                        exit(1);
                } else count_m++;
		printf("Got: %s\n", msg_buff[count_m-1]);
		msg_buff[count_m] = malloc(80);*/	
	}

	return 0;
}
