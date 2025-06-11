#include <stdio.h>

int main()
{
  char str_a[20];

  str_a[0] = 'H';
  str_a[1] = 'e';
  str_a[2] = 'l';
  str_a[3] = 'l';
  str_a[4] = ' ';
  str_a[5] = 'W';
  str_a[6] = 'o';
  str_a[7] = 'r';
  str_a[8] = 'l';
  str_a[9] = 'd';
  str_a[10] = '!';
  str_a[11] = '\n';
  str_a[12] = 0; // Null byte: tells any function dealing the string `str_a` to stop here.

  printf("%s", str_a);
}