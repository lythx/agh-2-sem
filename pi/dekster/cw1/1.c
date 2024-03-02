#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);
	float factorial = 1;
	for(int i = 2; i <= n; i++) {
		factorial *= i;
	}
	printf("%f\n", factorial);
}
