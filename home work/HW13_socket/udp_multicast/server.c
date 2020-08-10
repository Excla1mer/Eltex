#include "header.h"

#define M_PORT 8080
#define M_ADDR "224.0.1.1"
int main() {
	char buffer[80] = "Multicast msg";
	int fd;
	int len;
	struct sockaddr_in server;
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket:");
		exit(1);
	}
	memset(&server, 0, sizeof(server));

	server.sin_family    = AF_INET;  
	server.sin_addr.s_addr = inet_addr(M_ADDR);
	server.sin_port = htons(M_PORT); 

	len = sizeof(server);
	if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server, len) == -1) {
	    perror("Sendto:");
	    exit(1);
 	}
	return 0;
}
