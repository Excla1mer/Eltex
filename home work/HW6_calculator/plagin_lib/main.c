#include "header.h"

int main() {
	float result = 0.0;
	int count_of_funcs = 0;
	int count_of_libs = 0;
	int b;
	char a[255];
	char end[2];		// нужна для опроса пользователя при вводе функций с клавиатуры(хочет ли он закончить)
	char funcs[10][20]; 	// массив для имен функций 
	char Namelib[255];  	// хранит название считанной библиотеки
	char Namefuncs[255];	// хранит строку считанных функций из What_i_have
	void *ptr[10];		// указатели на библиотеки
	void *name;
	char (*Name)(char *);
	float (*func)(float);
	struct dirent **namelist;
        int n;
	memset(funcs, 0 , sizeof(funcs));
        n = scandir("plagins", &namelist, NULL, alphasort);// Считываем и сортируем всю директорию 
	b = n - 1;
	printf("%d\n", n);
        if (n == -1) {
           	perror("scandir");
               	exit(EXIT_FAILURE);
        }
        while ( b != 1) {// 0 и 1 записи являются служебными . и ..
		strncpy(Namelib, namelist[b]->d_name, 20);// Считываем имя библиотеки
		ptr[count_of_libs] = dlopen(Namelib, RTLD_NOW);
		if(!ptr[count_of_libs])		// проверка открытия библиотеки
			printf("Error of lib");
		count_of_libs++;	
               	free(namelist[b]);
		b--;
      	}
       	free(namelist);
	for(int i = 0; i < count_of_libs; i++) {
	
		n = 0;
		name = dlsym(ptr[i], "What_i_have");
		Name=name;
		Name(&Namefuncs);
		for(int j = 0; j < strlen(Namefuncs); j++) {
			if(Namefuncs[j] == '|') { // если в одной библиотеке несколько функций
				count_of_funcs++;
				n = 0;
			}
			else {
				funcs[count_of_funcs][n] = Namefuncs[j];
				n++;
			}
		
		}
		count_of_funcs++;
	
	}
	/*if(dlsym(ptr[0], "sum") != 0) {
		printf("Ok\n");
	
	}
	if(dlsym(ptr[0], "dsm") != 0) {
		printf("ok\n");
	}*/
// ---------------------Заполнение массива имен функций с клавиатуры-------------------------------
	/*do {
		do {
			
			printf("Enter library name: ");
        	        scanf("%s", &Namelib);
	                // Запись библиотеки в массив указателей на эти библиотеки
			ptr[count_of_libs] = dlopen(Namelib, RTLD_NOW);
			if(!ptr[count_of_libs]) // Проверка на существование введенной библиотеки
				printf("Wrong lib\n");
		}while(!ptr[count_of_libs]);
		count_of_libs++;
		// Запись информационной функции What_i_have в указатель на функцию 
		// What_i_have выведет строку с названиями всех функций имеющихся в библиотеке
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

	}while(strcmp(end, "y") == 0);*/
// ------------------------------------------------------------------------------------------------
	while(1) {	
		system("clear");
		draw(result, funcs, count_of_funcs);// Отрисовка калькулятора
		fgets(&a, 2, stdin);
		b = atoi(&a);
		for(int j = 0; j < count_of_libs; j++) {// Перебор всех введенных библиотек
			for(int i = 0; i < count_of_funcs; i++) {// Перебор всех добавленных функций
	                        if(i == b) {
					if(dlsym(ptr[j], funcs[i]) != 0) {// Функция нашлась
						func = dlsym(ptr[j], funcs[i]);
                                        	result = func(result);
						j = count_of_libs;
						break;
					}
        	                        else {
						//printf("Error of find function\n");
						break;
					}
                        	}

                	}

		}
		if( b == count_of_funcs ) // RESET
			result = 0.0;
		if( b == count_of_funcs + 1) { // EXIT
			_Exit(0);
		}
		scanf("%c", &a);
	}
}
