#include "header.h"

float sub(float Result) {
	float x;
	printf("%f - ", Result);
	scanf("%f", &x);
	Result -= x;
	return Result;
}
