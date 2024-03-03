#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float cos_taylor(float x);

int main(void)
{
  float a;
  printf("Podaj poczatek przedzialu: ");
  scanf("%f", &a);
  float b;
  printf("Podaj koniec przedzialu: ");
  scanf("%f", &b);
  float dx;
  printf("Podaj przyrost x: ");
  scanf("%f", &dx);
  float x = a;
  while(x <= b) {
    printf("%f ", x);
    printf("%f ", cos(x));
    printf("%f\n", cos_taylor(x));
    x += dx;
  }
  return 0;
}

// Przy duzych wartosciach x powyzej 5 zwraca bzdury (podnoszenie do wysokich poteg nie miesci sie we floacie)
float cos_taylor(float x) {
  float sum = 1;
  int i = 3;
  int factorial = 2;
  int sign = -1;
  float x2 = x*x;
  float p = x2;
  float val = 1;
  // Przy wysokich wartościach i jest problem z silnia
  while(i < 15) {
    val = sign * p / factorial;
    sum += val;
    sign = -sign;
    p *= x2;
    factorial *= i * (i + 1);
    i += 2;
  }
  return sum;
}
