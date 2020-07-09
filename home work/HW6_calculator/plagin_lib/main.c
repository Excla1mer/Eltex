#include "header.h"

int main() {
	float result = 0.0;
	int count_of_funcs = 0;
	int count_of_libs = 0;
	int b;
	char a[255];
	char end[2];
	char funcs[10][20];
	char Namelib[255];
	void *ptr[10];
	void *name;
	char (*Name)();
	float (*func)(float);
	
	do {
		printf("Enter library name: ");
		scanf("%s", &Namelib);
		ptr[count_of_libs] = dlopen(Namelib, RTLD_NOW);   
		if (!ptr[count_of_libs]) {
	        	fprintf(stderr,"dlopen() error: %s\n", dlerror());
	        	exit(1);
		};
		count_of_libs++;
       		name = dlsym(ptr[count_of_funcs], "What_i_have");
		Name=name;
		Name();
		do {
			printf("Enter func to add:");
	        	scanf("%s", &funcs[count_of_funcs]);
	        	count_of_funcs++;
	        	scanf("%c", &a);
		        printf("Do you want to enter more funcs? y/n : ");
		        fgets(&end, 2, stdin);

		}while(end == "y");
		scanf("%c", &a);
		printf("Do you want enter more libs? y/n : ");
		fgets(&end, 2, stdin);

	}while(strcmp(end, "y") == 0);
	scanf("%c", &a);
	while(1) {	
		system("clear");
		draw(result, funcs, count_of_funcs);
		fgets(&a, 2, stdin);
		b = atoi(&a);
		for(int j = 0; j < count_of_libs; j++) {
			for(int i = 0; i < count_of_funcs; i++) {
	                        if(i == b) {
					if(dlsym(ptr[j], funcs[i]) == 0) {
						func = dlsym(ptr[i], funcs[i]);
                                        	result = func(result);
						j = count_of_libs;
						break;
					}
        	                        else {
						break;
					}
                        	}

                	}

		}
		if( b == count_of_funcs )
			result = 0.0;
		if( b == count_of_funcs + 1) { 
			_Exit(0);
		}
		scanf("%c", &a);
	}
}
