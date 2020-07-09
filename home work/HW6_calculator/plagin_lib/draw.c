#include "header.h"

void draw(float Result, char funcs[10][20], int count_of_funcs) { // Результат операции, Массив имен функций, кол-во функций
	printf("---------------------\n");
	for(int i = 0; i < count_of_funcs; i++) { // Проходим по всем добавленным функциям
		printf("|  [%d] %-12s |\n", i, funcs[i]); // Выводим номер функции и ее название
	}
	printf("|  [%d] RESET        |\n", count_of_funcs);
	printf("|  [%d] EXIT         |\n", count_of_funcs + 1);
        printf("---------------------\n");
        printf("|Result|%-12.2f|\n", Result);
       	printf("---------------------\n");
}
