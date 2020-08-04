#include "header.h"

#define NAME_SINC_MSG "/sinc-msg"
#define NAME_SIGN "/signals11"
#define NAME_MSG "/messages11"
#define MAX_MSG 10
#define MAX_MSG_SIZE 128

unsigned int count_u; // count of users
unsigned int count_m; // count of messages 

mqd_t client[100];

struct mq_attr attr = {0, MAX_MSG, MAX_MSG_SIZE, 0};

struct new {
	char u_names[20][80];
	char msg_buff[100][81];
	char sender[100][80];
};

void* signals(void *param);



int main()  {
	struct new st;
	mqd_t msg;	
	char client_ch[80] = "/";
	pthread_t tid_sign;
	pthread_t tid_sinc_msg;
	if((msg = mq_open(NAME_MSG, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
                perror("MSG mq_open");
                exit(1);
    }
    printf("msg open\n");
	pthread_create(&tid_sign, NULL, signals, &st);
	while(1) {
		printf("waiting msg\n");
		if(mq_receive(msg, st.msg_buff[count_m], attr.mq_msgsize, 0) == -1) {
			perror("MSG mq_receive");
			exit(1);
		} else count_m++;
		for(int i = 0; i < count_u; i++) {
			if(mq_send(client[i], st.msg_buff[count_m-1], strlen(st.msg_buff[count_m-1]) + 1, 0) == -1) {
           		perror("SIGN mq_receive");
             	exit(1);
            }
		}
		if(mq_receive(msg, st.sender[count_m-1], attr.mq_msgsize, 0) == -1) {
			perror("MSG mq_receive");
			exit(1);
		}
		for(int i = 0; i < count_u; i++) {
			if(mq_send(client[i], st.sender[count_m-1], strlen(st.sender[count_m-1]) + 1, 0) == -1) {
           		perror("SIGN mq_receive");
             	exit(1);
            }
		}
	}
	return 0;
}


void* signals(void *param) {
	
	mqd_t sign;
	struct new *st;
	st = (struct new*)param;
	
	char client_ch[80] = "/";
	printf("open sign\n");
	if((sign = mq_open(NAME_SIGN, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
		perror("SIGN mq_open:");
		exit(1);
	}
	while(1) {
		printf("waiting sign\n");
		if(mq_receive(sign, st->u_names[count_u], attr.mq_msgsize, 0) == -1) {
			perror("SIGN mq_receive");
                        exit(1);
                }
        strcat(client_ch, st->u_names[count_u]);
        printf("%s\n", client_ch);
		if((client[count_u] = mq_open(client_ch, O_RDWR)) == -1) {
         	perror("client mq_open:");
            exit(1);
        }
        printf("client_ch open\n");
        sleep(1);
        for(int i = 0; i <= count_m; i++) {
        	if(i == count_m) {
        		if(mq_send(client[count_u], "end-sinc-msg", 16, 0) == -1) {
        	    	perror("client mq_send");
    	    		exit(1);
	      		}
	      		printf("end-sinc-msg\n");
	      		break;
        	}
        	if(mq_send(client[count_u], st->msg_buff[i], strlen(st->msg_buff[i]) + 1, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}
        }
        for(int i = 0; i <= count_m; i++) {
        	if(i == count_m) {
        		if(mq_send(client[count_u], "end-sinc-sender", 16, 0) == -1) {
        	    	perror("client mq_send");
    	    		exit(1);
	      		}
	      		printf("end-sinc-sender\n");
	      		break;
        	}
        	if(mq_send(client[count_u], st->sender[i], strlen(st->sender[i]) + 1, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}
        }
        for(int i = 0; i <= count_u+1; i++) {
        	if(i == count_u) {
        		if(mq_send(client[count_u], "end-sinc-name", 16, 0) == -1) {
        	    	perror("client mq_send");
    	    		exit(1);
	      		}
	      		printf("end-sinc-name\n");
	      		break;
        	}
        	if(mq_send(client[count_u], st->u_names[i], strlen(st->u_names[i]) + 1, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}
        }
        for(int i = 0; i <= count_u; i++) {
        	if(mq_send(client[i], "new-user", 16, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}
      		if(mq_send(client[i], st->u_names[count_u], strlen(st->u_names[count_u]) + 1, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}

        }
		memset(client_ch, 0, 80);
		strcat(client_ch, "/");
		count_u++;
		
	}

}