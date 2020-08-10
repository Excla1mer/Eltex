#include "header.h"

#define M_PORT 8080
#define M_ADDR "224.0.1.1"
int main(int argc, char *argv[]) {
	int fd;
	char buffer[80];
	int len;
	struct sockaddr_in server, client;
  struct ip_mreqn socket_param;

  socket_param.imr_multiaddr.s_addr = inet_addr(M_ADDR);
  socket_param.imr_address.s_addr = INADDR_ANY;
  socket_param.imr_ifindex = 0;


  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket:");
    exit(1);
  }
	if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &socket_param, sizeof(struct ip_mreqn)) == -1) {
    perror("setsockopt");
    exit(1);
  }
  memset(&server, 0, sizeof(server));
  server.sin_family    = AF_INET;  
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(M_PORT);

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
