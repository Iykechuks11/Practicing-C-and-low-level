#include <stdio.h> // For printf
#include "utils.h" // Include our own header

// Definition of the utility function
void print_message(const char *message) {
    printf("Utility Message: %s\n", message);
}

// Definition of another utility function
int add(int a, int b) {
    return a + b;
}