#include <stdio.h>

#define N 5

int main() {
	int a[N] = {1, 2, 3, 4, 5};
	for(int i = N-1; i >= 0; i--) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
