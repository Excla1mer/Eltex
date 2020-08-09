#include "header.h"

#define B_PORT 8080
#define B_ADDRES "10.0.2.255"

int main(int argc, char *argv[]) {
	int fd;
	char buffer[80];
	int len;
	struct sockaddr_in server, client;
    
  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket:");
    exit(1);
  }
	
  memset(&server, 0, sizeof(server));
  server.sin_family    = AF_INET;  
  server.sin_addr.s_addr = inet_addr(B_ADDRES);
  server.sin_port = htons(B_PORT);
	len = sizeof(server);
  if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1) {
    perror("pthread_server Bind:");
    exit(1);
  }
	
	if(recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len) == -1) {
    perror("Recvfrom:");
    exit(1);
	}
  printf("%s\n", buffer);
}
