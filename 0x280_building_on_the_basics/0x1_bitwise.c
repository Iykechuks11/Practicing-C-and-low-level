#include <stdio.h>

int main() {
  int i, bit_a, bit_b;

  printf("bitwise OR operator | \n");

  for (i = 0; i < 4; i++) {
    bit_a = (i & 2) / 2; // Get the second bit
    // 0000 | 0010
    // 0001 | 0010
    // 0010 | 0010
    // 0011 | 0010
    bit_b = (i & 1); // Get the first bit
    // 0000 | 0001
    // 0001 | 0001
    // 0010 | 0001
    // 0011 | 0001
    printf("%d | %d = %d\n", bit_a, bit_b, bit_a | bit_b);
  }

  // int p = 1 & 2;

  // printf("%d\n", p);
}