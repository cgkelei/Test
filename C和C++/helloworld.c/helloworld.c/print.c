#include <stdio.h>
void Binary()
{
	//int input = 0;
	//scanf("%d", &input);
	// int MASK = sizeof(int) * 8 - 1;
	// while (MASK)
	// {
	//	 int val = input & MASK>1? 1:0;
	//	 printf("%d", val);
	//	 input >> MASK;
	//	 MASK--;
	// }
	
}
int main(int argc, char *argv[])
{
	//float x = 110.4454f;
	//int val = 34;
	//int a = 97;
	//printf("hello guys\n");
	//printf("%6i,%4d\n", 200,203);
	//printf("%0.2f,%g\n",x , 0.9993000);
	//printf("%x,%o,%u\n", val, val, val);
	//printf("%c\n", a);
	//printf("%p\n", val);

	int a = 0;
	int b = 1;

	//			1   1
	printf("%d %d %d\n", b = a++ + (a++ + 2), b, a = b++);
	printf("a=%p ,&b = %p\n", a, b);

	return 0;
}