#include <stdio.h>

#define N 5

int main() {
	int a[N][N];
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if((i + j) < (N - 1)) {
				a[i][j] = 0;
			}
			else {
				a[i][j] = 1;
			}
			printf("%d ", a[i][j]);
       	 	}
		printf("\n");
	}
	return 0;
}
