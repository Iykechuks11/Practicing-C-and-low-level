#include <stdio.h>

int main() {
  int i;

  char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[5] = {1, 2, 3, 4, 5};

  char *char_pointer; // Will expect char, which is 1 byte per
  int *int_pointer;   // Will expect int, which is 4 byte per

  char_pointer = int_array; // 4 byte is assigned into a 1 byte container, hence error is expected
  int_pointer = char_array; // 1 byte into 4 byte

  for (i = 0; i < 5; i++) { // Iterate throguh the int array with int_pointer.
    printf("[integer pointer] points to %p, which contains the integer %c\n", 
    int_pointer, *int_pointer);
    int_pointer = int_pointer + 1;
  }

  for (i = 0; i < 5; i++) { // Iterate through the char array with the char_pointer.
    printf("[char pointer] points to %p, which contains the char '%d'\n",
    char_pointer, *char_pointer);
    char_pointer = char_pointer + 1;
  }
  
}