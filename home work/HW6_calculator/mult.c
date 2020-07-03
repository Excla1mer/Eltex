#include "header.h"

float mult(float Result) {
	float x;
	printf("%.4f * ", Result);
	scanf("%f", &x);
	Result *= x;
	return Result;
}
