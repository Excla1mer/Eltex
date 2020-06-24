#include <stdio.h>
struct test {
	char a;
	int b;
};

int main() {
	struct test test1;
	struct test *ptr;
	char arr[10] = {'a', 0, 0, 0, 1,
			1, 0, 0, 0, 0};
	ptr = &arr;
	printf("%c\n",  ptr->a);
	printf("%d\n", ptr->b);
	return 0;
}
