#include <stdio.h>

int main() {
	int a = 0xAACCBBFF;
	char *ptr;

	ptr = &a;
	printf("\t\t---Input value---\n");
	for(int i = 0; i < sizeof(int); i++)
	{
		printf("%d byte - %x \n",i+1 ,*ptr & 0xFF);
		ptr++;
	}
	ptr = &a;
	ptr = ptr + 2;
	printf("\t\t---Modifed value---\n");
	*ptr = 0x77;
	ptr = &a;
	for(int i = 0; i < sizeof(int); i++)
        {
                printf("%d byte - %x \n",i+1 ,*ptr & 0xFF);
                ptr++;
        }
	return 0;
}
