#include "header.h"

#define SHARED_MEM "/shared_mem"
#define COUNT_U "/count_u"
#define COUNT_M "/count_m"


mqd_t client[100];

struct new {
	char u_names[50][80];
	char msg_buff[100][81];
	char sender[100][80];
};

int users;
int messages;
sem_t *count_u;
sem_t *count_m;
int main()  {
	struct new *st;
   
    int shm_fd;


    if((shm_fd = shm_open(SHARED_MEM, O_CREAT|O_RDWR, 0777)) == -1) {
        perror("shm_open");
        exit(1);
    }
    if(ftruncate(shm_fd, sizeof(struct new)) == -1) {
        perror("ftruncate");
        exit(1);
    }
    st = (struct new*)mmap(NULL, sizeof(struct new), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    /*if( == -1) {
        perror("mmap");
        exit(1);
    } */
    memset(st, 0 , sizeof(struct new));
    count_u = sem_open(COUNT_U, O_CREAT, 0777, 0);
    count_m = sem_open(COUNT_M, O_CREAT, 0777, 0);
    /*if(sem_open(COUNT_U, O_CREAT, 0777, 0) == -1) {
        perror("sem_open count_u");
        exit(1);
    }
    if(sem_open(COUNT_M, O_CREAT, 0777, 0) == -1) {
        perror("sem_open count_m");
        exit(1);
    }*/
    sem_getvalue(count_u, &users);
    sem_getvalue(count_m, &messages);
    for(int i = 0; i < users; i++){
        sem_wait(count_u);
    }
    for(int i = 0; i < messages; i++){
        sem_wait(count_m);
    }
    while(1) {
        sleep(1000);
    }

	return 0;
}