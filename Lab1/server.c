#include "header.h"

#define NAME_SINC_MSG "/sinc-msg"
#define NAME_SIGN "/signals0"
#define NAME_MSG "/messages2"
#define MAX_MSG 10
#define MAX_MSG_SIZE 8192

unsigned int count_u; // count of users
unsigned int count_m; // count of messages 

unsigned int sgn_prio_send = 1;
unsigned int sgn_prio_receive = 2;
unsigned int sgn_prio_sinc_msg_receive = 4; // приоритет для синхронизации сообщений 
unsigned int sgn_prio_sinc_msg_send = 3; // приоритет для синхронизации сообщений 
unsigned int sgn_prio_sinc_names = 5; // приоритет для синхронизации имен


mqd_t client[100];

struct sinc_struct {
	char **u_names;
	char **msg_buff;
};

struct new {
	char u_names[20][80];
	char msg_buff[100][81];
};

void* signals(void *param) {
	
	mqd_t sign;
	struct new *st;
	//struct sinc_struct *st;
	//st = (struct sinc_struct*)param;
	st = (struct new*)param;
	struct mq_attr attr;
	char client_ch[80] = "/";
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MSG;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	printf("open sign\n");
	if((sign = mq_open(NAME_SIGN, O_RDWR | O_CREAT, 0777, 0)) == -1) {
		perror("SIGN mq_open:");
		exit(1);
	}
	while(1) {
		//st->u_names[count_u] = malloc(80);
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
        for(int i = 0; i <= count_m; i++) {
        	if(i == count_m) {
        		if(mq_send(client[count_u], "end-sinc-msg", attr.mq_msgsize, 0) == -1) {
        	    	perror("client mq_send");
    	    		exit(1);
	      		}
	      		printf("end-sinc-msg\n");
	      		break;
        	}
        	if(mq_send(client[count_u], st->msg_buff[i], attr.mq_msgsize, 0) == -1) {
            	perror("client mq_send");
        		exit(1);
      		}
      		//printf("%s\n", st->msg_buff[i]);

        }

        /*if(mq_send(sign, st->u_names[count_u], attr.mq_msgsize, sgn_prio_send) == -1) {
            perror("SIGN mq_receive");
        	exit(1);
      	}
        printf("sended sign %s\n", st->u_names[count_u]);*/
		memset(client_ch, 0, 80);
		strcat(client_ch, "/");
		count_u++;
		
	}

}

/*void *sinc_msg(void *param) {
	char buff[80];
	char **msg_buff = (char **)param;
	mqd_t sinc_msg;
	struct mq_attr attr;
	attr.mq_flags = 0;
        attr.mq_maxmsg = MAX_MSG;
        attr.mq_msgsize = MAX_MSG_SIZE;
        attr.mq_curmsgs = 0;
	if((sinc_msg = mq_open(NAME_SINC_MSG, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
                perror("SIGN mq_open:");
                exit(1);
        }
	
	while(1) {
		printf("wait sinc-msg\n");
		if(mq_receive(sinc_msg, buff, attr.mq_msgsize, &sgn_prio_sinc_msg_receive) == -1) {
                        perror("SIGN mq_receive");
                        exit(1);
                }
                printf("got sinc-msg: %s\n", buff);
		if(strcmp(buff, "Ok") == 0) {
			memset(buff, 0, sizeof(buff));
			strcat(buff, "end-sinc-msg");
			for(int i = 0; i < count_m; i++) {
				if(mq_send(sinc_msg, msg_buff[i], attr.mq_msgsize, sgn_prio_sinc_msg_send) == -1) {
                	        	perror("SIGN mq_receive");
        	                	exit(1);
	               	}
	               	printf("send sinc-msg\n");
			}

			if(mq_send(sinc_msg, buff, attr.mq_msgsize, sgn_prio_sinc_msg_send) == -1) {
                           	perror("SIGN mq_receive");
                               	exit(1);
                      	}
                      	printf("send end-sinc-msg: %s\n", buff);

		} else {
			printf("sinc-msg-wrong\n");
		}
		
	}
}*/


int main()  {
	//struct sinc_struct st;
	struct new st;
	//st.u_names = malloc(sizeof(char*));
	//st.msg_buff = malloc(sizeof(char*));
	mqd_t msg;	
	char client_ch[80] = "/";
	//char** u_names = malloc(sizeof(char*));
	//char** msg_buff = malloc(sizeof(char*));
	pthread_t tid_sign;
	pthread_t tid_sinc_msg;
	struct mq_attr attr;
	//st.msg_buff[count_m] = malloc(80);
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
	if((msg = mq_open(NAME_MSG, O_RDWR | O_CREAT, 0777, 0)) == -1) {
                perror("MSG mq_open");
                exit(1);
    }
    printf("msg open\n");
	pthread_create(&tid_sign, NULL, signals, &st);
	//pthread_create(&tid_sinc_msg, NULL, sinc_msg, msg_buff);
	while(1) {
		printf("waiting msg\n");
		//st.msg_buff[count_m] = malloc(80);
		if(mq_receive(msg, st.msg_buff[count_m], attr.mq_msgsize, NULL) == -1) {
			perror("MSG mq_receive");
			exit(1);
		} else count_m++;
		
		for(int i = 0; i < count_u; i++) {
			if(mq_send(client[i], st.msg_buff[count_m-1], attr.mq_msgsize, 0) == -1) {
           		perror("SIGN mq_receive");
             	exit(1);
            }
         	//printf("sended msg %s\n", st.msg_buff[count_m-1]);
			/*memset(client_ch, 0, sizeof(client_ch));
			strcat(client_ch, "/");*/
		}
	}
	return 0;
}
