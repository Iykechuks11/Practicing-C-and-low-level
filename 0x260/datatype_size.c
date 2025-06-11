#include <stdio.h>

int main()
{
	printf("The 'int' data type is\t\t %ld bytes\n", sizeof(int));
	printf("The 'unsigned int' data type is\t %ld bytes\n", sizeof(unsigned int));
	printf("The 'long long int' data type is\t %ld bytes\n", sizeof(long long int));

	printf("The 'char' data type is\t %ld bytes\n", sizeof(char));
}
