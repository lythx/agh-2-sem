#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);
	int f1 = 0;
	int f2 = 1;
	int prod = f1 * f2;
	while(prod < n) {
		int temp = f1;
		f1 = f2;
		f2 = temp + f2;
		prod = f1 * f2; 
	}
	if(prod == n) {
		printf("tak");
	} else {
		printf("nie");
	}
}
