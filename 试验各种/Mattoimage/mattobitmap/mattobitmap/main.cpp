// WinBmp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

HINSTANCE g_hInst = NULL;

void DrawBmp( HDC hDC )
{	//����λͼ��Դ
	HBITMAP hBmp = LoadBitmap( g_hInst,
		MAKEINTRESOURCE( IDB_BALL01 ) );
	//��ȡλͼ�������Ϣ
	BITMAP bmpInfo = { 0 };
	GetObject( hBmp, sizeof( bmpInfo ), &bmpInfo );
	//��������λͼ��DC
	HDC hBmpDC = CreateCompatibleDC( hDC );
	//��λͼ����hBmpDC
	HBITMAP hOldBmp = ( HBITMAP )
		SelectObject( hBmpDC, hBmp );
	//����λͼ
	BitBlt( hDC, 100, 100, bmpInfo.bmWidth,
		bmpInfo.bmHeight, hBmpDC,
		0, 0, SRCCOPY );
	//�������
	StretchBlt( hDC, 200, 100, 300, 300,
		hBmpDC, 0, 0, bmpInfo.bmWidth,
		bmpInfo.bmHeight, SRCCOPY );
	//ȡ��λͼ
	SelectObject( hBmpDC, hOldBmp );
	//ɾ��DC
	DeleteDC( hBmpDC );
	//ɾ��λͼ
	DeleteObject( hBmp );
}

void OnPaint( HWND hWnd, UINT nMsg,
	WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps = { 0 };
	HDC hDC = BeginPaint( hWnd, &ps );

	DrawBmp( hDC );

	EndPaint( hWnd, &ps );
}

LRESULT CALLBACK WndProc( HWND   hWnd,
	UINT   nMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	switch (nMsg)
	{
	case WM_PAINT:
		OnPaint( hWnd, nMsg, wParam, lParam );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, nMsg,
		wParam, lParam );
}

BOOL RegisterWnd( LPSTR pszClassName )
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof( wce );
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = HBRUSH( COLOR_WINDOW );
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInst;
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = pszClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;

	ATOM nAtom = RegisterClassEx( &wce );
	if (0 == nAtom)
	{
		return FALSE;
	}

	return TRUE;
}

HWND CreateWnd( LPSTR pszClassName )
{
	HMENU hMenu =
		LoadMenu( g_hInst, MAKEINTRESOURCE( IDR_MAIN ) );
	HWND hWnd = CreateWindowEx( 0,
		pszClassName, "MyWnd",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, hMenu, g_hInst,
		NULL );
	return hWnd;
}

void DisplayWnd( HWND hWnd )
{
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
}

void Message()
{
	MSG msg = { 0 };
	while (GetMessage( &msg, NULL, 0, 0 ))
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

int APIENTRY WinMain( HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow )
{
	g_hInst = hInstance;
	RegisterWnd( "MYWND" );
	HWND hWnd = CreateWnd( "MYWND" );
	DisplayWnd( hWnd );
	Message();
	return 0;
}



