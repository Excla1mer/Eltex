#include <stdio.h>
#include <string.h>
#define N 5

struct book {
	char Name[10];
	unsigned long int Number;
};

int main() {
	struct book list[N] = {{{'S', 'e', 'r', 'g', 'e', 'y'}, 88005553535},
				{{'D', 'i','m', 's'}, 654862135}};
	char a;
	char str[255];
	int b;
	do {
		printf("---------Menu-------\n");
		printf("|  [1] View list   |\n");
		printf("|  [2] Add user    |\n");
		printf("|  [3] Remove user |\n");
		printf("--------------------\n");
		//scanf("%c", &a);
		fgets(&a, 3, stdin);
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
                       //Ydalenie usera po imeni
			case '3':
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
		//scanf("%c", &a);
	}while(1);

}
