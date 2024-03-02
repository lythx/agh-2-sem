#include <stdio.h>
#include <math.h>

int non_decreasing(int n);

int is_prime(int n);

int main(void) {
	int n;
	scanf("%d", &n);
	printf("2 ");
	for(int i = 3; i < n; i += 2) {
		if(non_decreasing(i) && is_prime(i)) {
			printf("%d ", i);
		}
	}
	return 0;
}

int non_decreasing(int n) {
	int last = -1;
	while(n > 0) {
		int a = n % 10;
		if(a < last) {
			return 0;
		}
		last = a;
		n /= 10;
	}
	return 1;
}

int is_prime(int n) {
	if(n == 2) {
		return 1;
	}
	if(n % 2 == 0 || n < 2) {
		return 0;
	}
	for(int i = 3; i < n; i += 2) {
		if(n % i == 0) {
			return 0;
		}
	}
	return 1;
}
