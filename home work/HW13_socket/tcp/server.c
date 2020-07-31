#include "header.h"

#define PORT 8080

int main() {
	char hi[80] = "Hi, ";
	char str[80];
	char buffer[80];
	int fd;
	int fd1;
	struct sockaddr_in client, server;
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket:");
		exit(1);
	}
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));
	
	server.sin_family    = AF_INET;  
    	server.sin_addr.s_addr = INADDR_ANY; 
    	server.sin_port = htons(PORT); 

	if(bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("Bind:");
		exit(1);
	}
	int len, n;
	len = sizeof(server);
	if ((listen(fd, 5)) == -1) { 
        		perror("Listen"); 
        		exit(1); 
    	}
	while(1) {
		
    		if((fd1 = accept(fd, (struct sockaddr *)&client, &len)) == -1) {
    			perror("accept");
    			exit(1);
    		}
    		printf("accept\n");
		printf("WAIT MSG\n");
		if((n = recv(fd1, buffer, sizeof(buffer), 0)) == -1) {
			perror("Recv");
			exit(1);
		}
		printf("got msg\n");
		buffer[n] = '\0';
		printf("%s\n", buffer);
		strcpy(str, hi);
		strcat(str, buffer);
		if(send(fd1, str, strlen(str), 0) == -1) {
			perror("Sendto:");
			exit(1);
		}
		printf("send msg\n");
		memset(str, 0, 80);
		memset(buffer, 0, 80);
	}
	return 0;
}
