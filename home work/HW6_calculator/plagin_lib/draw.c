#include "header.h"

void draw(float Result, char funcs[10][20], int count_of_funcs) {
	printf("---------------------\n");
	for(int i = 0; i < count_of_funcs; i++) {
		printf("|  [%d] %-12s |\n", i, funcs[i]);
	}
	printf("|  [%d] RESET        |\n", count_of_funcs);
	printf("|  [%d] EXIT         |\n", count_of_funcs + 1);
        printf("---------------------\n");
        printf("|Result|%-12.2f|\n", Result);
       	printf("---------------------\n");
}
