#include <stdio.h>
#include <math.h>

int suma_dziel(int n);

int main(void) {
	int start, end;
	scanf("%d", &start);
	scanf("%d", &end);
	int count = 0;
	for(int i = start; i <= end; i++) {
		if(suma_dziel(i) == i) {
			printf("%d ", i);
			count += 1;
		}
	}
	printf("ilosc: %d", count);
	return 0;
}


int suma_dziel(int n) {
	int s = 1;
	int i = 2;
	while(i < sqrt(n)) {
		if(n % i == 0) {
			s += i + n / i;
		}	
		i++;	
	}
	if(i * i == n) {
		s += i;
	}
	return s;
}
