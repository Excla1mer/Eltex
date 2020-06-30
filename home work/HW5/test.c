#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *f;
int IsPassOk(void);

int main(void)
{
	int PwStatus;
	
	puts("Enter password:");
	PwStatus = IsPassOk();
	
	if (PwStatus == 0) {
		printf("Bad password!\n");
		exit(1);
	} else {
		printf("Access granted!\n");
	}

	return 0;
}

int IsPassOk(void)
{
	char Pass[12];
	char *ptr = &Pass;
	f = fopen("file.txt", "r");
	fread(&Pass, sizeof(char),36, f);
	//gets(Pass);
	printf("%s\n", Pass);
	//printf("%x\n", *ptr);
	return 0 == strcmp(Pass, "test");
}
