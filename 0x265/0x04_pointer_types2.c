#include <stdio.h>

int main() 
{
  int i;
  char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[5] = {1, 2, 3, 4, 5};

  char *char_pointer;
  int *int_pointer;

  char_pointer = int_array; // points to the first address of the elements in this array
  int_pointer = char_array;

  // printf("%s\n", char_pointer);

  for(i=0; i < 5; i++) 
  { // Iterate through the int array with the int_pointer.
    printf("[integer pointer] points to %p, which contains the char %c\n", int_pointer, *int_pointer);
    int_pointer = int_pointer + 1;
  }

  for(i=0; i < 5; i++) 
  { // Iterate through the char array with the char_pointer.
    printf("[char pointer] points to %p, which contains the char '%d'\n", char_pointer, *char_pointer);
    char_pointer = char_pointer + 1;
  }
}