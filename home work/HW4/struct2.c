#include "header.h"

int main() {

	struct book *list = malloc(sizeof(struct book));;
	char a;
	int Quantity = 0;
	char str[255];
	int find = 0;

	do {
		printf("\t---------Menu-------\n");
		printf("\t|  [1] View list   |\n");
		printf("\t|  [2] Add user    |\n");
		printf("\t|  [3] Find user   |\n");
		printf("\t|  [4] Remove user |\n");
		printf("\t|  [5] Exit        |\n");
		printf("\t--------------------\n");
		scanf("%c", &a);
		//fgets(&a, 2, stdin);
		switch(a) {
			//Viviod vsego spiska
			case '1':
				for(int i = 0; i < Quantity; i++) {
					if(list[i].Number  != 0)
						printf("Name: %s Number: %ld\n", list[i].Name, list[i].Number);
				}
				break;
			//Dobavleni novogo usera v spisok
			case '2':
				for(int i  = 0; i < Quantity; i++) {
					if(list[i].Number == 0) {
						printf("Enter name:");
						scanf("%s", list[i].Name);
						printf("Enter Number: ");
						scanf("%ld", &list[i].Number);
						break;
					}
					//If no free space
					if( i == (Quantity - 1) )
					{
						list = realloc(list, (sizeof(struct book) * (Quantity + 1)));
						printf("Enter name:");
                                                scanf("%s", list[Quantity].Name);
                                                printf("Enter Number: ");
                                                scanf("%ld", &list[Quantity].Number);
						Quantity++;
						break;
					}
				}
				//If list empty
				if ( Quantity == 0 )
				{
					Quantity++;
					printf("Enter name:");
                                        scanf("%s", list[0].Name);
                                        printf("Enter Number: ");
                                        scanf("%ld", &list[0].Number);

				}
                                break;
			//Find user
                       case '3':
                       	printf("Enter Name:");
				scanf("%s", str);
				for(int i = 0; i < Quantity; i++) {
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
                       //Delete user by name
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
			//Exit
			case '5':
				_Exit(0);
				break;
			default :
				break;
		}
		scanf("%c", &a);
	}while(1);

}
