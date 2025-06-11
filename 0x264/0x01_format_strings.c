#include <stdio.h>
#include <string.h>

int main()
{
  int a, b, c, hex;
  char d[10];

  a = 1;
  b = -10;
  strcpy(d, "Hello");
  hex = 1044;

  printf("%d\n", a); // `%d` prints decimals
  // printf("%x\n", hex);
  // printf("%s\n", d);
}