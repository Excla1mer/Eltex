#include "header.h"

char What_i_have() {
        char return_name[255] = {'s','u','b'};
        return Draw(return_name);
}
void Draw(char *return_name) {
        printf("------------------\n");
        printf("|Functions in lib|\n");
        printf("------------------\n");
        printf("%s\n", return_name);

}


float sub(float Result) {
	float x;
	printf("%.4f - ", Result);
	scanf("%f", &x);
	Result -= x;
	return Result;
}
