#include "header.h"
extern pthread_mutex_t mut[5];
pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;

void destr(void *whant) {
	free(whant);
}
void create_key(void) {
	pthread_key_create(&key, destr);
}



void *customer_key() {
	//int *ptr;
	//ptr = (int *)param;
	int *whant;
	pthread_once(&once, create_key);
	whant = pthread_getspecific(key);
	if(whant == NULL) {
		whant = calloc(2, sizeof(int));
		pthread_setspecific(key, whant);
	}
	for(int i = 0; i < 5; i++)
	{
		store[i] = 450 + rand() % 100;
		if(i < 3){
			*whant = 9800 + rand() % 400;
			*(whant + 1) = pthread_self();
		}
	}
	int *ptr;
	ptr = whant;
	int ex = 0;
	int i;
	do {
		do {
			ex = 0;
			i = rand () % 5;
			// Проверяем доступен ли нам mutex
			if(pthread_mutex_trylock(&mut[i]) == 0) {
			// Если в магазине есть товар и
   	             	// потребитель хочет больше, чем
                	// есть в магазине
				if(store[i] != 0 && *ptr >= store[i]) {
					*ptr = *ptr - store[i];
					store[i] = 0;
					ex = 1;
					printf("I am {%d}, went to the %d store, need %d products\n",*(ptr + 1), i, *ptr);
					pthread_mutex_unlock(&mut[i]);
					break;
				} else if(store[i] != 0 && *ptr < store[i]) { // Есть товар, но потребитель хочет меньше чем есть в магазине
					store[i] = store[i] - *ptr;
					*ptr = 0;
					ex = 1;
					printf("I am {%d}, went to the %d store, products done --------------!\n",*(ptr + 1), i);
					pthread_mutex_unlock(&mut[i]);
					//pthread_exit();
					break;
				} else if(store[i] == 0) { // Мы попали в магазин, но он пуст
					printf("I am {%d}, went to the %d store, but it was empty\n", *(ptr + 1), i);
					pthread_mutex_unlock(&mut[i]);
					break;
				}
				else {	// Проверка на невозможное событие
					printf("I am {%d} and i dont know why i am heare\n", *(ptr + 1));
				
				}

				//pthread_mutex_unlock(&mut[i]);
			}
			else {
				printf("I am {%d}, went to the %d store, but it closed\n", *(ptr + 1), i);
				ex = 0;
			
			}

		} while (ex == 0);// Если  mutex не доступен пробуем зарандомить новый магазин
		
		sleep(5);
	} while(*ptr != 0);
	
}

void *worker(void *param) {
	int *work;
	work = (int *)param;
	int i;
	do {	// Выполняется пока есть работа *work = 1
		do { 
		i = rand () % 5;					// Выбирает случайный магазин
			if(pthread_mutex_trylock(&mut[i]) == 0) { 	// Проверяет свободен ли он
				printf("In [%d] store was %d products\n", i, store[i]);
				store[i] = store[i] + 500;		
				printf("I am worker, unload products to the %d store\n", i);
				printf("In [%d] store become %d products \n", i, store[i]);
				pthread_mutex_unlock(&mut[i]);
				break; // Выходим из бесконечного цикла
			}
		} while(1);
		sleep(1);
	} while(*work != 0);

}
