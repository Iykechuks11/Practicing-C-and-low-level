#include <stdio.h>

int main() {
  int old = 0;
  int current = 1;
  int next;
  
  printf("First number in Fibonacci series: %d\n", old);

  int n = 10; // Number of Fibonacci numbers to generate
  for (int i = 0; i <= n; i++) {
    next = old + current;
    old = current;
    current = next;
    printf("%d ", next);
  }
  printf("\n");

}