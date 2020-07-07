#include "header.h"

float my_div(float Result) {
	float x;
	do {
		printf("%.4f / ", Result);
		scanf("%f", &x);
		if( x == 0) {
			printf("Wrong input!!!\n");
		}
		else {
			Result /= x;
			return Result;
		}
	} while( x == 0);
}

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

float mult(float Result) {
	float x;
	printf("%.4f * ", Result);
	scanf("%f", &x);
	Result *= x;
	return Result;
}

float sub(float Result) {
	float x;
	printf("%.4f - ", Result);
	scanf("%f", &x);
	Result -= x;
	return Result;
}

float sum(float Result) {
	float x;
	printf("%.4f + ", Result);
	scanf("%f", &x);
	Result += x;
	return Result;
}
