#include "header.h"

int main() {
	float result = 0.0;
	char a[255];
	int b;
	while(1) {
		system("clear");
		draw(result);
		fgets(&a, 2, stdin);
		b = atoi(&a);
		switch(b) {
			case 1:
				result = sum(result);
				break;
			case 2:
				result = sub(result);
                                break;
			case 3:
				result = mult(result);
                                break;
			case 4:
				result = my_div(result);
                                break;
			case 5:
				result = 0.0;
                                break;
			case 6:
				_Exit(0);
                                break;
			default :
				printf("Wrong input!\n");
				break;
		}
	}

}
