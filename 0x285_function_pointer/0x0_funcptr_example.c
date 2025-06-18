// Function pointers
/*
 Pointers are primarily known to be used 
 for variables and contains the mem add 
*/

#include <stdio.h>

int fun_one() {
  printf("This is function one\n");
  return 1;
}

int fun_two() {
  printf("This is function two\n");
  return 2;
}

int main() {
  int value;
  int (*function_ptr)();

  function_ptr = fun_one;
  printf("function_prt is 0x%08x\n", function_ptr);
  value = function_ptr();
  printf("value returned was %d\n", value);

  function_ptr = fun_two;
  printf("function_prt is 0x%08x\n", function_ptr);
  value = function_ptr();
  printf("value returned was %d\n", value);

}