#include "header.h"
#define N 5

int main() {
	struct book list[N] = {{{'S', 'e', 'r', 'g', 'e', 'y'}, 88005553535},
				{{'D', 'i','m', 's'}, 654862135}};
	char a;
	int b;
	char str[255];
	int find = 0;
	do {
		printf("\t---------Menu-------\n");
		printf("\t|  [1] View list   |\n");
		printf("\t|  [2] Add user    |\n");
		printf("\t|  {3} Find user   |\n");
		printf("\t|  [4] Remove user |\n");
		printf("\t--------------------\n");
		scanf("%c", &a);
		//fgets(&a, 2, stdin);
		switch(a) {
			//Viviod vsego spiska
			case '1':
				for(int i = 0; i < N; i++) {
					if(list[i].Number  != 0)
						printf("Name: %s Number: %ld\n", list[i].Name, list[i].Number);
				}
				break;
			//Dobavleni novogo usera v spisok
			case '2':
				for(int i  = 0; i < N; i++) {
					if(list[i].Number == 0) {
						printf("Enter name:");
						scanf("%s", list[i].Name);
						printf("Enter Number: ");
						scanf("%ld", &list[i].Number);
						break;
					}
				}
                                break;
                       case '3':
                       	printf("Enter Name:");
				scanf("%s", str);
				for(int i = 0; i < N; i++) {
					if(strcmp(str, list[i].Name) == 0) {
						find++;
						printf("Name: %s Number: %ld\n", list[i].Name, list[i].Number);
					}
				}
				if(find == 0) {
					printf("No one found ;(\n"); 
				}
				else {
					find = 0;
				}
                       	break;
                       //Ydalenie usera po imeni
			case '4':
				printf("Enter Name:");
				scanf("%s", str);
				for(int i = 0; i < N; i++) {
					if(strcmp(str, list[i].Name) == 0) {
						memset(list[i].Name, 0, sizeof(list[i].Name));
						list[i].Number = 0;
						break;
					}
				}
                                break;
			default :
				break;
		}
		scanf("%c", &a);
	}while(1);

}
