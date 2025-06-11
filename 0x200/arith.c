#include <stdio.h>

int main() {
  int a = 5;
  int b = 10;
  int sum = a + b;
  int diff = a - b;
  int prod = a * b;
  float quot = (float)a / (float)b;

  int incafter = 0;
  int incbefore = 0;
  incafter = a++;
  incbefore = ++b;
  printf("Increment after: %d\n", incafter);
  printf("Increment before: %d\n", incbefore);
  printf("a: %d\n", a);
  printf("b: %d\n", b);

  printf("Sum: %d\n", sum);
  printf("Difference: %d\n", diff);
  printf("Product: %d\n", prod);
  printf("Quotient: %.2f\n", quot);

  return 0;
}