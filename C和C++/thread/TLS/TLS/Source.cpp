#include <windows.h>
#include <conio.h>
#include <stdio.h>
char* g_pszText1 = NULL;
__declspec( thread ) char* g_pszText2 = NULL;
void Print()
{
	printf( "%s\n", g_pszText1 );
	printf( "%s\n", g_pszText2 );
	printf( "\n\n" );
}
DWORD WINAPI ThreadProc1( LPVOID lpParameter )
{
	CHAR * str = ( CHAR* )lpParameter;
	g_pszText1 = ( CHAR * )malloc( 100 );
	memset( g_pszText1, 0, 100 );
	strcpy( g_pszText1, str );

	g_pszText2 = ( char * )malloc( 100 );
	memset( g_pszText2, 0, 100 );
	strcpy( g_pszText2, str );

	while (1)
	{
		Print();
		Sleep( 1000 );
	}
	return 0;
}
void Create()
{
	DWORD dwThread = 0;
	CHAR szText[] = "Thread 1--------------------";
	HANDLE hThread = CreateThread( NULL, 0, ThreadProc1, szText, 0, &dwThread );

	CHAR szText2[] = "Thread 2--------------------";
    hThread = CreateThread( NULL, 0, ThreadProc1, szText2, 0, &dwThread );

	CHAR szText3[] = "Thread 3--------------------";
	hThread = CreateThread( NULL, 0, ThreadProc1, szText3, 0, &dwThread );



	_getch();
}
int main( int argc, char **argv )
{
	Create();
	
	return 0;
}