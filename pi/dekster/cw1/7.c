#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
  srand(time(NULL));
  float a;
  printf("Podaj poczatek przedzialu: ");
  scanf("%f", &a);
  float b;
  printf("Podaj koniec przedzialu: ");
  scanf("%f", &b);
  int n;
  printf("Podaj ilosc punktow: ");
  scanf("%d", &n);
  // Ilosc punktow wylosowanych pod wykresem
  int count = 0;
  for(int i = 0; i < n; i++) {
    // Losowy float z przedzialu <a, b>
    float x = a + ((float)rand() / RAND_MAX) * (b - a);
    // Losowy float z przedzialu <0, 1> 
    float y = ((float)rand() / RAND_MAX);
    // Uzywam abs bo licze prostakat nad Ox (o wymiarach (b - a) X 1)
    // (nie zmienia to szansy na trafienie w pole ograniczone wykresem)
    if(fabs(sin(x)) > y) {
      count += 1;
    }
  }
  // Wynik to stosunek punktow pod wykesem do wszystkich
  // punktow pomnozony przez pole calego obszaru prostokata
  float result = ((float)count / n) * (b - a);
  printf("%f ", result);
  return 0;
}
