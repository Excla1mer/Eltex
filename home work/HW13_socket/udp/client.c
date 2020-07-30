#include "header.h"

#define PORT 8080

int main(int argc, char *argv[]) {
	int fd;
	char buffer[80];
	int len;
	strcpy(buffer, argv[1]);
	struct sockaddr_in server;
        if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
                perror("Socket:");
                exit(1);
        }
	memset(&server, 0, sizeof(server));
        server.sin_family    = AF_INET;  
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);
	len = sizeof(server);
	if(sendto(fd, buffer, strlen(buffer), MSG_CONFIRM, &server, len) == -1) {
                        perror("Sendto:");
                        exit(1);
     	}
	if(recvfrom(fd, buffer, sizeof(buffer), MSG_WAITALL, &server, &len) == -1) {
                        perror("Recvfrom:");
                        exit(1);
      	}
	printf("%s\n", buffer);


}
