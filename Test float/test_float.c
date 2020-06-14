#include  <stdio.h>


int main() {
	float count = 0.0;
	while(1) {
		if(count>16700000)
			printf("%f\n", count);
		count = count + 1.0;
	}
}
