#include "header.h"
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

#define PORT 8080

int clients_ports[100];
int count_of_clients;

void* pthread_server() {
	int fd;
	struct sockaddr_in client; 
	int n, len;
	char buffer[80];
	pthread_mutex_lock(&mut);
	client.sin_family    = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(8081 + count_of_clients);
	count_of_clients++;
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
		printf("wait client %d\n", fd);
		if((n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)) == -1) {
			perror("pthread_server Recvfrom:");
			exit(1);
		}
		buffer[n] = '\0';
		if(strcmp(buffer, "exit") == 0){
			close(fd);
			break;
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
	//inet_aton(ADDR, &inp);
	server.sin_family    = AF_INET;  
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT); 

	if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1) {
		perror("Bind");
		exit(1);
	}
	int len, n;
	len = sizeof(clients[count_of_clients]);
	while(1) {
		printf("wait  client\n");
		if((n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)) == -1) {
			perror("Recvfrom:");
			exit(1);
		}
		buffer[n] = '\0';
		printf("%s\n", buffer);
		pthread_create(&clients_pthread[count_of_clients], NULL, pthread_server, 0);
		if(sendto(fd, &count_of_clients, sizeof(int), 0, (struct sockaddr*)&client, len) == -1) {
			perror("Sendto:");
			exit(1);
		}
		printf("sended count_of_clients\n");
		
		memset(str, 0, 80);
		memset(buffer, 0, 80);
	}
	return 0;
}
