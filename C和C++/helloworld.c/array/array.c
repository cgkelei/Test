#include <stdio.h>
int main(int argc, char *argv[])
{

	int arr[] = { 34, 34, 34 };
	for (int i = 0; i<sizeof(arr) / sizeof(int);i++)
	{
		printf("addr:%p\n", &arr);
		printf("1.%d\n", i[arr]);
		printf("2.%d\n", *(i+arr));
		printf("3.%d\n", arr[i]);
		printf("4.%d\n", *(&(arr)+i));
		printf("\n");
	}


	return 0;
}