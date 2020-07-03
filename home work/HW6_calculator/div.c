#include "header.h"

float my_div(float Result) {
	float x;
	do {
		printf("%f / ", Result);
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
