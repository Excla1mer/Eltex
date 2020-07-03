#include <stdio.h>
// Program for creating file with desired binary sequence
union test {
	char a;
	int b[9];

};
FILE *f;
int main() {
	union test my_test;
	my_test.b[0] = 0x30313233;
	my_test.b[1] = 0x34353637;
	my_test.b[2] = 0x38393a3b;
	my_test.b[3] = 0xffffde5c;
	my_test.b[4] = 0x00007fff;
	my_test.b[5] = 0xffffdf00;
	my_test.b[6] = 0x00007fff;
	my_test.b[7] = 0x5555525d;
	my_test.b[8] = 0x005555;
	f = fopen("file1.txt", "w");
	fwrite(&my_test.a, sizeof(my_test.b), 1, f);
}
