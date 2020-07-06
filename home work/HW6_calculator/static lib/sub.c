#include "header.h"

float sub(float Result) {
	float x;
	printf("%.4f - ", Result);
	scanf("%f", &x);
	Result -= x;
	return Result;
}
