#include <stdio.h>

int main(int argc, char *argv[])
{

	printf("%d,%d,%d\n", ~20, ~-5, ~4);
	unsigned int n = -1;
	printf("%u,%x,%d\n", n, n, n);
	int m = -1;
	printf("%x,%x\n", n >> 3, m >> 3);
	printf("%x,%x\n", n << 3, m << 3);

	m = 300;
	printf("%d,%d\n", m << 3, m >> 3);

	return 0;
}