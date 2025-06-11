#include <stdio.h>

int sayHello() {
    printf("Hello, World!\n");
    return 0;
}

int factorial(int n) {
  // n * n - 1 * n - 2
  if (n == 0) {
    printf("Factorial of 0 is 1\n");
    return 1;
  }

  for (int i = n - 1; i > 0; i--) {
    n *= i;
  }
  printf("Factorial of %d is %d\n", n, n);
  // int result = n;
  // for (int i = 1; i < n; i++) {
  //   result *= n - i;
  // }
  // printf("Factorial of %d is %d\n", n, result);
  // printf("\n");


}

int main() {
  sayHello();
  factorial(5);
}