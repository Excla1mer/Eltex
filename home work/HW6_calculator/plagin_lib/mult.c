#include "header.h"

char What_i_have(char *name[255]) {
        char return_name[255] = {'m','u','l','t'};
        strcpy(name, return_name);
	//return Draw(return_name);
}
void Draw(char *return_name) {
        printf("------------------\n");
        printf("|Functions in lib|\n");
        printf("------------------\n");
        printf("%s\n", return_name);

}


float mult(float Result) {
	float x;
	printf("%.4f * ", Result);
	scanf("%f", &x);
	Result *= x;
	return Result;
}
