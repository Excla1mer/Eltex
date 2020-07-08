#include "header.h"

void draw(float Result) {
	printf("---------------------\n");
        printf("|  [1] +            |\n");
        printf("|  [2] -            |\n");
        printf("|  [3] *            |\n");
        printf("|  [4] /            |\n");
        printf("|  [5] Reset        |\n");
        printf("|  [6] Exit         |\n");
        printf("---------------------\n");
        printf("|Result|%-12.2f|\n", Result);
       	printf("---------------------\n");
}
