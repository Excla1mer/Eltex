#include "header.h"
pthread_mutex_t mut[5] = PTHREAD_MUTEX_INITIALIZER;

int main() {
	srand(time(NULL));
	int whant[3][2];
       	int work = 1;
	pthread_t tid_c[3]; 	// tid для покупателей
	pthread_t tid_w;	// tid для рабочего
	for(int i = 0; i < 5; i++)
	{
		store[i] = 450 + rand() % 100;
		if(i < 3){
			whant[i][0] = 9800 + rand() % 400;
			whant[i][1] = i;
		}
	}
	printf("[0] %d [1] %d [2] %d [3] %d [4] %d\n", store[0], store[1], store[2], store[3], store[4]);
	pthread_create(&tid_w, NULL, worker, &work); 	// Создаем поток для рабочего
	for(int i = 0; i < 3; i++) {
		pthread_create(&tid_c[i], NULL, customer, &whant[i]);	// Создаем потоки для покупателей
	}
	for(int i = 0; i < 3; i++) {
		pthread_join(tid_c[i], NULL); 	// Дожидаемся  завершения покупателей 
	}
	work = 0;	// Меняем флаг работы на 0 (т.е. работы больше нету)
	pthread_join(tid_w, NULL); 	// Дожидаемся завершения рабочего

	return 0;
}
