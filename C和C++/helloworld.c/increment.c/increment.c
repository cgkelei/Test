#include <stdio.h>
int main(int argc, char **argv)
{
	int a = 0; int b = 20;
	a++;
	b++;
	int c = 0, d = 0;

	printf("%d--%d\n", a, b);
	printf("%d-%d\n", ++c, ++d);
	return 0;
}