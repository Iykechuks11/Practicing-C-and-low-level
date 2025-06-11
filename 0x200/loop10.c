#include <stdio.h>

int main() {
    int i = 0;
    int sum = 0;

    // Loop from 1 to 10
    for (i = 1; i <= 10; i++) {
        sum += i; // Add the current number to the sum
        printf("The sum of numbers from 1 to 10 is: %d\n", sum); // Print the result
    }


    return 0;
}