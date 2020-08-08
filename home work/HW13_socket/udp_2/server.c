#include "header.h"
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

#define PORT 8080
#define CONST_SERVERS 5 // Количество заранее созданных серверов
#define MAX_of_CLIENTS 2000

uint16_t clients_ports[MAX_of_CLIENTS][2]; // Хранит номера портов для подключения клиентов {[][0] - номер порта|[][1] - занятость}
unsigned int count_of_clients;
unsigned int max_count_clients_connect;

void* pthread_server(void *param) { // Используя полученный порт создает сокет и ожидает сообщение клиента 
	uint16_t *port_i = (uint16_t *)param;
	uint16_t *ID_port = port_i + 1; 
	int fd;
	struct sockaddr_in client; 
	int n, len;
	char buffer[80];
	pthread_mutex_lock(&mut);
	client.sin_family    = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(*port_i);
	pthread_mutex_unlock(&mut);
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("pthread_server Socket:");
		exit(1);
	}
	if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1) {
		perror("pthread_server Bind:");
		exit(1);
	}
	len = sizeof(client);
	while(1) {
		printf("wait client %d, port %d\n", fd, *port_i);
		if((n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)) == -1) {
			perror("pthread_server Recvfrom:");
			exit(1);
		}
		buffer[n] = '\0';
		if(strcmp(buffer, "exit") == 0){
			count_of_clients--;
			*ID_port = 0;
			if(count_of_clients > CONST_SERVERS) {	
				close(fd);
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


int main() {
	char str[80];
	char buffer[80];
	int fd;
	max_count_clients_connect = CONST_SERVERS;
	pthread_t clients_pthread[100];
	struct sockaddr_in client, server;
	struct sockaddr_in clients[100];
	struct in_addr inp;
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
		buffer[n] = '\0';
		printf("%s\n", buffer);
		if(count_of_clients <= max_count_clients_connect) {
			for(int i = 0; i < MAX_of_CLIENTS; i++){
				if(clients_ports[i][1] == 0) {
					if(sendto(fd, &clients_ports[i][0], sizeof(int), 0, (struct sockaddr*)&client, len) == -1) {
						perror("Sendto:");
						exit(1);
					}
					printf("sended clients_ports %d\n", clients_ports[i][0]);
					clients_ports[i][1] = 1;
					break;
				}
			}
		} else {
			max_count_clients_connect = count_of_clients;
			clients_ports[count_of_clients][0] = 8081 + count_of_clients;
			pthread_create(&clients_pthread[count_of_clients], NULL, pthread_server, &clients_ports[count_of_clients]);
			if(sendto(fd, &clients_ports[count_of_clients][0], sizeof(int), 0, (struct sockaddr*)&client, len) == -1) {
				perror("Sendto:");
				exit(1);
			}
			printf("sended clients_ports %d\n", clients_ports[count_of_clients][0]);
			clients_ports[count_of_clients][1] = 1;
		}	
		memset(str, 0, 80);
		memset(buffer, 0, 80);
	}
	return 0;
}
