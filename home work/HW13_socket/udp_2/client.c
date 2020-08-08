#include "header.h"

#define PORT 8080

int main(int argc, char *argv[]) {
	int fd;
	char buffer[80] = "hello";
	char tmp[10];
	int len;
	int count;
	struct sockaddr_in server, server1;
    
  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket:");
    exit(1);
  }
	memset(&server, 0, sizeof(server));
  server.sin_family    = AF_INET;  
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(PORT);
	len = sizeof(server);

	if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server, len) == -1) {
    perror("Sendto:");
    exit(1);
 	}
 	printf("sended request\n");
	if(recvfrom(fd, &count, sizeof(int), 0, (struct sockaddr*)&server, &len) == -1) {
    perror("Recvfrom:");
    exit(1);
	}
	printf("got %d\n", count);
	server1.sin_family    = AF_INET;  
  server1.sin_addr.s_addr = INADDR_ANY;
  server1.sin_port = htons(count);

	while(1) {
		printf("input msg: ");
		scanf("%s", buffer);
    if(strcmp(buffer, "exit") == 0)
      break;
		if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server1, len) == -1) {
      perror("Sendto:");
      exit(1);
    }
 		printf("sended msg\n");
 		printf("wait server1\n");
    if(recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server1, &len) == -1) {
    	perror("Recvfrom:");
    	exit(1);
		}
		printf("%s\n", buffer);
	}
  if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server1, len) == -1) {
    perror("Sendto:");
    exit(1);
  }
}
