#include <stdio.h>

int main() {
	int a = 0x00CCAABB;
	int c;
	for(int i = 0; i <= 24; i+=8) {
		c = (a >> i) & 0xFF;
		printf("0x%x\n",c);
	}
	a = a & 0xFF55FFFF;
	printf("0x%x\n",a);
	return 0;
}
