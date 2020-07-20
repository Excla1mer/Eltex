#include "header.h"
long sum = 0;
void *func(void *param) {
	long tmp;
	long *ptr;
	ptr = (long *)param;
	for(long j = 0; j < 10000000; j++) {
		tmp = *ptr;
		tmp++;
		*ptr = tmp;
	}
	return 0;
}

int main() {
	pthread_t tid[500];

	for(int i = 0; i < 500; i++) {
		pthread_create(&tid[i], NULL, func, &sum);
	}
	for(int i = 0; i < 500; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("%ld\n", sum);
	return 0;
}
