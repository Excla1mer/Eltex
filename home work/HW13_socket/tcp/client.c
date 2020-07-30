#include "header.h"

#define PORT 8080

int main(int argc, char *argv[]) {
	int fd;
	char buffer[80];
	int len;
	int n;
	strcpy(buffer, argv[1]);
	struct sockaddr_in server;
        if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("Socket:");
                exit(1);
        }
        
	memset(&server, 0, sizeof(server));
        server.sin_family    = AF_INET;  
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);
	len = sizeof(server);
	if(connect(fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("connect");
		exit(1);
	}
	
	if(send(fd, buffer, strlen(buffer), MSG_CONFIRM) == -1) {
		perror("Send");
		exit(1);
	}
	printf("send msg\n");
	/*if(sendto(fd, buffer, strlen(buffer), MSG_CONFIRM, &server, len) == -1) {
          	perror("Sendto:");
          	exit(1);
     	}
	if(recvfrom(fd, buffer, sizeof(buffer), MSG_WAITALL, &server, &len) == -1) {
          	perror("Recvfrom:");
           	exit(1);
      	}*/
      	printf("wait msg\n");
      	if((n = recv(fd, buffer, sizeof(buffer), MSG_WAITALL)) == -1) {
			perror("Recv");
			exit(1);
	}
	
	buffer[n] = '\0';
	printf("%s\n", buffer);


}
