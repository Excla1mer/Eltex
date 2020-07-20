#include "header.h"

void func(void *param) {
	int *ptr;
	ptr = (int *)param;
	printf("I am %d thread\n", *ptr);
}

int main() {
	void **status = 0;
	pthread_t tid[5];
	int a[5];
	for(int i = 0; i < 5; i++) {
		a[i] = i;
		pthread_create(&tid[i], NULL, func, &a[i]);
	}
	for(int i = 0; i < 5; i++) {
		pthread_join(&tid[i], status);
	}
	return 0;
}
