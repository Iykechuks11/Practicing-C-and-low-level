#include <stdio.h>
#include <string.h>

int main()
{
	char a[20];
	char *pointer;
	char *pointer2;

	strcpy(a, "Hello, world!\n");
	pointer = a;
	puts(pointer);

	pointer2 = pointer + 2;
	puts(pointer2);
	puts(pointer + 2);
	strcpy(pointer2, "y you guys!\n");
	puts(pointer);
}
