#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsPassOk(void);
FILE *f;
int main(void)
{
	int PwStatus;
	printf("%p\n", main);
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
#ifdef GDB
	f = fopen("file1.txt", "r");
	fread(&Pass, sizeof(char),36, f);
	printf("%s\n", Pass);
#endif
#ifdef SAM
	f = fopen("file1.txt", "r");
	gets(Pass);
	printf("%s\n", Pass);
#endif
	fclose(f);
	return 0 == strcmp(Pass, "test");
}
