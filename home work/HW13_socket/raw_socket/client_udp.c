#include "header.h"

#define PORT 8080
#define S_PORT 8081
#define SIZE_PACKAGE 128
/* Структура описывает пришедший пакет от сервера по полям */
struct package {
	char network[20]; 	// Заголовок сетевого уровня 20 байт
	char udphdr[8];		// Заколовок транспортного уровня 8 байт
	char msg[100]; 		// Полузная нагрузка 100 байт
};

struct udphdr {
	u_short	uh_sport;		/* source port */
	u_short	uh_dport;		/* destination port */
	u_short	uh_ulen;		/* udp length */
	u_short	uh_sum;			/* udp checksum */
};

int main(int argc, char *argv[]) {
	int fd, fd1;
	char buffer[128];
	int len;
	short *dport;
	memset(buffer, 0, 128);
	struct sockaddr_in server, client;
	struct udphdr *header;
	struct package *receive;
/* Выставляю указатель на структуру заголовка udp в начало буффера кадра и заполняю его данными */
	header = (struct udphdr*)buffer;
	header->uh_sport = htons(S_PORT);
	header->uh_dport = htons(PORT);
	header->uh_ulen  = htons(SIZE_PACKAGE);
	header->uh_sum   = htons(0);
/* Вставляю сообщение в конец кадра */
	strcat(&buffer[8], argv[1]);
/* Создаю сокет с портом 8081, чтобы не получать ICMP пакеты с ошибкой PORT UNREACHABLE */
	client.sin_family    = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(S_PORT);

	if((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket:");
		exit(1);
	}
	if(bind(fd1, (struct sockaddr*)&client, sizeof(client)) == -1) {
		perror("Bind");
		exit(1);
	}
/***************************************************************************************/
    if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) {
        perror("Socket:");
        exit(1);
    }
	memset(&server, 0, sizeof(server));

    server.sin_family    	= AF_INET;  
    server.sin_addr.s_addr 	= INADDR_ANY;
    server.sin_port 		= htons(PORT);

	len = sizeof(server);
	if(sendto(fd, buffer, SIZE_PACKAGE, 0, (struct sockaddr*)&server, len) == -1) {
        perror("Sendto:");
        exit(1);
 	}
 	receive = (struct package*)buffer;
	dport = (short *)&receive->udphdr[2];
 	while(1) {
		if(recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) == -1) {
		    perror("Recvfrom:");
		    exit(1);
		}
		/* Обрабатываю все пакеты и смотрю какие предназначены мне, а какие нет */
		if(ntohs(*dport) == S_PORT) {
			printf("It's mine: ");
			printf("%s\n", receive->msg);
		} else {
			printf("That's not mine: ");
			printf("%s\n", receive->msg);
		}
	}
}
