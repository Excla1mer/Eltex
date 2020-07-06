#include "header.h"

int main() {

	struct book *list = malloc(sizeof(struct book));;
	char a[255];
	int Quantity = 0;
	int b;
	char str[255];
	int find = 0;

	do {
		system("clear");
		printf("\t---------Menu-------\n");
		printf("\t|  [1] View list   |\n");
		printf("\t|  [2] Add user    |\n");
		printf("\t|  [3] Find user   |\n");
		printf("\t|  [4] Remove user |\n");
		printf("\t|  [5] Exit        |\n");
		printf("\t--------------------\n");
		fgets(&a, 2, stdin);
		b = atoi(&a);
		switch(b) {
			//Viviod vsego spiska
			case 1:
				printf("\tView list\n");
				for(int i = 0; i < Quantity; i++) {
					if(list[i].Number  != 0)
						printf("Name: %s Number: %ld\n", list[i].Name, list[i].Number);
				}
				printf("Press Enter to return to the menu\n");
				scanf("%c",&str);
				break;
			//Dobavleni novogo usera v spisok
			case 2:
				printf("\tAdd user\n");
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
                       case 3:
				printf("\tFind user\n");
	                       	printf("Enter Name:");
				*str = "";
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
				printf("Press Enter to return to the menu\n");
				scanf("%c", &str);
                	       	break;
                       //Delete user by name
			case 4:
				printf("\tDelete user\n");
				printf("Enter Name:");
				scanf("%s", str);
				for(int i = 0; i < Quantity; i++) {
                                        if(strcmp(str, list[i].Name) == 0) {
                                                find++;
                                        }
                                }
				switch(find) {

					case 1:
						for(int i = 0; i < Quantity; i++) {
		                                        if(strcmp(str, list[i].Name) == 0) {
                		                        	memset(list[i].Name, 0, sizeof(list[i].Name));
                                		                list[i].Number = 0;
                                              			break;
							}
                               			}
						break;
					case 0:
						printf("Wrong enter!! No one found to delete!\n");
						break;
					default :
						printf("Two or more users with this name! Please enter Users Number to delete!\n");
						printf("Enter Number:");
						unsigned long int x;
						scanf("%ld", &x);
						for(int i = 0; i < Quantity; i++) {
        		                                if(x == list[i].Number) {
                        		                        memset(list[i].Name, 0, sizeof(list[i].Name));
                                        		        list[i].Number = 0;
                                              			break;
                                       			 }
	                                	}

						break;

				}
                                break;
			//Exit
			case 5:
				free(list);
				_Exit(0);
				break;
			default :
				break;
		}
		scanf("%c",&a);
	}while(1);

}
