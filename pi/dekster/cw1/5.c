#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));
	int x = rand() % 101;
  int low = 0;
  int high = 100;
  while(1) {
    // n z przedzialu otwartego dlatago dodane i odjete 1
    int n = low + 1 + rand() % (high - low - 1);
    printf("%d ", n);
    if(x == n) {
      return 0;
    } else if (x < n) {
      high = n;
    } else {
      low = n;
    }
  }
}
