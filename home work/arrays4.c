#include <stdio.h>

#define N 9

int main() {
	int a[N][N];
	int i, j;
	int k = 0;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			a[i][j] = 0;
//--------------Заполнение периметра матрицы---------------------
	for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        printf("%d ", a[i][j]);
                }
                printf("\n");
        }
	i = 0;
	for(j = 0; j < N; j++) {
		a[i][j] = k;
		k++;
	}
	j = N - 1;
	for(i = 1; i < N; i++) {
		a[i][j] = k;
		k++;
	}
	i = N - 1;
	for(j = N - 2;  j >= 0; j--) {
		a[i][j] = k;
		k++;
	}
	j = 0;
	for(i = N - 2; i > 0; i--) {
		a[i][j] = k;
		k++;
	}
//-----------------------------------------------------------------------
	printf("\n\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%d\t ", a[i][j]);
		}
		printf("\n");
	}

	i = 1;
	j = 1;
	while(k <= N*N -1) {
		//Движение направо
		//printf("%d", a[i][j]);
		while(a[i][j] == 0 ) {
			a[i][j] = k;
			//printf("%d ", a[i][j]);
			k++;
			j++;
			if(a[i][j] != 0) {
				j--;
				i++;
				break;
			}
		}
		//Вниз
		while(a[i][j] == 0) {
			a[i][j] = k;
			//printf("%d ", a[i][j]);
			k++;
			i++;
			if(a[i][j] != 0) {
				i--;
				j--;
				break;
			}
		}
		//Влево
		while(a[i][j] == 0) {
			a[i][j] = k;
			//printf("%d ", a[i][j]);
			k++;
			j--;
			if(a[i][j] != 0) {
				j++;
				i--;
				break;
			}
		}
		//Вверх
		while(a[i][j] == 0) {
			a[i][j] = k;
			//printf("%d ", a[i-1][j]);
			k++;
			i--;
			if(a[i][j] != 0) {
				i++;
				j++;
				break;
			}
		}
	}
	printf("\n\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%d\t ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
