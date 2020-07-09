#include "header.h"

char What_i_have() {
        char return_name[255] = {'m','y','_','d','i','v'};
        return Draw(return_name);
}
void Draw(char *return_name) {
        printf("------------------\n");
        printf("|Functions in lib|\n");
        printf("------------------\n");
        printf("%s\n", return_name);

}


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
