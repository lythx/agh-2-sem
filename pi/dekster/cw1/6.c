#include <stdio.h>

int main(void)
{
  int k;
  printf("Podaj klucz: ");
  scanf("%d", &k);
  int n;
  printf("Podaj ilosc znakow: ");
  scanf("%d", &n);
  char str[256];
  printf("Podaj ciag znakow: ");
  scanf("%s", str);
  for(int i = 0; i < n; i++) {
    int code = str[i];
    // Kody dużych liter
    if (code >= 65 && code <= 90) {
      str[i] = 65 + (code + k - 65) % 25;
    }
    // Kody małych liter
    else if (code >= 97 && code <= 122) {
      str[i] = 97 + (code + k - 97) % 25;
    }
  }
  printf("%s", str);
  return 0;
}
