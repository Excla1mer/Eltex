#include "header.h"
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

#define PORT 8080
#define CONST_SERVERS 1 // Количество заранее созданных серверов
#define MAX_of_CLIENTS 2000
#define NAME_ASK "/clients_ask"

#define MAX_MSG 10
#define MAX_MSG_SIZE 512

uint16_t clients_ports[MAX_of_CLIENTS][2]; // Хранит номера портов для подключения клиентов {[][0] - номер порта|[][1] - занятость}
unsigned int count_of_clients;
unsigned int max_count_clients_connect;

struct mq_attr attr = {0, MAX_MSG, MAX_MSG_SIZE, 0};

void* pthread_server(void *param) { // Используя полученный порт создает сокет и ожидает сообщение клиента 
	uint16_t *port_i = (uint16_t *)param;
	uint16_t *ID_port = port_i + 1; 
	int fd, fd1;
	struct sockaddr_in client, clients_endp; 
	int n, len;
	char buffer[80];
	mqd_t client_ask;
	int ex = 0;
	client.sin_family    = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(*port_i);
	
	len = sizeof(client);
	
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("pthread_server Socket:");
		exit(1);
	}
	
	if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1) {
		perror("pthread_server Bind:");
		exit(1);
	}
	printf("bind %d\n", fd);
	if((client_ask = mq_open(NAME_ASK, O_RDWR)) == -1) {
        perror("pthread client_ask mq_open:");
        exit(1);
    }
    //pthread_mutex_lock(&mut);
    while(ex == 0) {
    	printf("pthread %d, waiting clients in clients_queue\n", fd);
	    if(mq_receive(client_ask, (char *)&clients_endp, attr.mq_msgsize, 0) == -1) {
			perror("pthread client_ask mq_receive");
			exit(1);
		}
		
		if((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("pthread_server Socket:");
			exit(1);
		}
		/*if(bind(fd1, (struct sockaddr*)&clients_endp, sizeof(clients_endp)) == -1) {
			perror("pthread_server Bind:");
			exit(1);
		}*/	
		if(sendto(fd1, port_i, sizeof(uint16_t), 0, (struct sockaddr*)&clients_endp, len) == -1) {
			perror("pthread_server Sendto:");
			exit(1);
		}
		close(fd1);
		//pthread_mutex_unlock(&mut);
		
		
		while(1) {
			printf("wait client %d, port %d\n", fd, *port_i);
			if((n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)) == -1) {
				perror("pthread_server Recvfrom:");
				exit(1);
			}
			buffer[n] = '\0';
			if(strcmp(buffer, "exit") == 0){
				
				*ID_port = 0;
				if(count_of_clients > CONST_SERVERS) {	
					printf("delete %d\n", fd);
					/*mq_unlink(NAME_ASK);
					close(client_ask);*/
					count_of_clients--;
					ex = 1;
					close(fd);
					break;
				} else  {
					printf("port %d free\n", *port_i);
					count_of_clients--;
					break;
				}
				
			}
			buffer[0] = '9';
			if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&client, len) == -1) {
				perror("pthread_server Sendto:");
				exit(1);
			}
		}
	}
	printf("End pthread\n");
}


int main() {
	char str[80];
	char buffer[80];
	int fd;
	mqd_t client_ask;
	max_count_clients_connect = CONST_SERVERS;
	pthread_t clients_pthread[100];
	struct sockaddr_in client, server;
	struct sockaddr_in clients[100];
	struct in_addr inp;

	if((client_ask = mq_open(NAME_ASK, O_RDWR | O_CREAT, 0777, &attr)) == -1) {
        perror("client_ask mq_open");
        exit(1);
    }

	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket:");
		exit(1);
	}
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));

	server.sin_family    = AF_INET;  
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT); 

	if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1) {
		perror("Bind");
		exit(1);
	}
	int len, n;
	len = sizeof(clients[count_of_clients]);
	for(int i = 0; i < CONST_SERVERS; i++) {
		clients_ports[i][0] = 8081 + i;
		pthread_create(&clients_pthread[i], NULL, pthread_server, &clients_ports[i]);
	}
	while(1) {
		printf("wait  client\n");
		if((n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)) == -1) {
			perror("Recvfrom:");
			exit(1);
		}
		count_of_clients++;
		printf("clients on server %d\n", count_of_clients);
		if(mq_send(client_ask, (char *)&client, sizeof(struct sockaddr_in), 0) == -1) {
       		perror("clients_ask mq_receive");
         	exit(1);
        }
		if(count_of_clients > CONST_SERVERS) {
			if(count_of_clients > max_count_clients_connect) {
				max_count_clients_connect = count_of_clients;
				clients_ports[count_of_clients][0] = 8080 + count_of_clients;
			}
			pthread_create(&clients_pthread[count_of_clients], NULL, pthread_server, &clients_ports[count_of_clients]);
		} 	
		memset(str, 0, 80);
		memset(buffer, 0, 80);
	}
	return 0;
}
