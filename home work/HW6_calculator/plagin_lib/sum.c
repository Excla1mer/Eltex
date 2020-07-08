#include "header.h"
char global_name[5] = "sum";

float sum(float Result) {
	float x;
	printf("%.4f + ", Result);
	scanf("%f", &x);
	Result += x;
	return Result;
}
