#include "header.h"

int main() {
	float result = 0.0;
	char a[255];
	void *ptr;
	void *name;
	float (*func_sum)(float);
	ptr = dlopen("/home/sergey/Eltex/home work/HW6_calculator/plagin_lib/libsum.so", RTLD_NOW);
	name = dlsym(ptr, "sum");
	func_sum=name;
	result = func_sum(result);
	printf("%f\n", result);
	int b;
	/*while(1) {
		system("clear");
		draw(result);
	}*/

}
