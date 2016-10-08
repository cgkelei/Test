#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.h"
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	DWORD nvalue = ( DWORD )lpParameter;
	for (int nIndex = 0; nIndex < 18;nIndex++)
	{
		printf( "Thread Proces1------------------------%d\n", nvalue );
	
	}
	return 0;
}
DWORD WINAPI ThreadProc2( LPVOID lpParameter )
{
	DWORD nvalue = ( DWORD )lpParameter;
	for (int nIndex = 0; nIndex < 18; nIndex++)
	{
		printf( "Thread Proces2------------------------%d\n", nvalue );
		
	}
	return 0;
}
DWORD WINAPI ThreadProc3( LPVOID lpParameter )
{
	DWORD nvalue = ( DWORD )lpParameter;
	for (int nIndex = 0; nIndex < 18; nIndex++)
	{
		printf( "Thread Proces3------------------------%d\n", nvalue );
	
	}
	return 0;
}
DWORD WINAPI ThreadProc4( LPVOID lpParameter )
{
	DWORD nvalue = ( DWORD )lpParameter;
	for (int nIndex = 0; nIndex < 18; nIndex++)
	{
		printf( "Thread Proces4------------------------%d\n", nvalue );
		
	}
	return 0;
}


void Create()
{

	
	DWORD dwThread = 0;
	DWORD nvalue = 100;
	HANDLE hThread1 = CreateThread( NULL, 0, ThreadProc1, (LPVOID)nvalue,CREATE_SUSPENDED, &dwThread );

	ResumeThread( hThread1 );
	printf( "Thread1 iD%d\n", dwThread );
	printf( "Thread1 Handle%p\n", hThread1 );
	WaitForSingleObject( hThread1, INFINITE );
	nvalue = 200;
	HANDLE hThread2 = CreateThread( NULL, 0, ThreadProc2, ( LPVOID )nvalue, CREATE_SUSPENDED, &dwThread );
	ResumeThread( hThread2 );
	printf( "Thread2 iD%d\n", dwThread );
	printf( "Thread2 Handle%p\n", hThread2 );
	WaitForSingleObject( hThread2, INFINITE );
	nvalue = 400;
	HANDLE hThread3 = CreateThread( NULL, 0, ThreadProc3, ( LPVOID )nvalue, CREATE_SUSPENDED, &dwThread );
	ResumeThread( hThread3 );
	printf( "Thread3 iD%d\n", dwThread );
	printf( "Thread3 Handle%p\n", hThread3 );
	WaitForSingleObject( hThread3, INFINITE );
	nvalue = 500;
	HANDLE hThread4 = CreateThread( NULL, 0, ThreadProc4, ( LPVOID )nvalue, CREATE_SUSPENDED, &dwThread );
	ResumeThread( hThread4 );
	printf( "Thread4 iD%d\n", dwThread );
	printf( "Thread4 Handle%p\n", hThread4 );
	WaitForSingleObject( hThread4, INFINITE );
	CloseHandle( hThread1 );
	CloseHandle( hThread2 );
	CloseHandle( hThread3 );
	CloseHandle( hThread4 );

}

int main( int argc, char** argv )
{
	Create();
	_getch();
	return 0;
}