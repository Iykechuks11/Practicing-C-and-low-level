#include <stdio.h>  // For printf
#include "utils.h"  // Include our utility functions header

int main() {
    int num1 = 10;
    int num2 = 5;
    int sum;

    printf("Hello from main program!\n");

    // Call a function from utils.c
    print_message("This is a test of the utility function.");

    // Call another function from utils.c
    sum = add(num1, num2);
    printf("The sum of %d and %d is: %d\n", num1, num2, sum);

    return 0; // Indicate successful execution
}