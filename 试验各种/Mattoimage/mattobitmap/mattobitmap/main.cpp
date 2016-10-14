// WinBmp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

HINSTANCE g_hInst = NULL;

void DrawBmp( HDC hDC )
{	//加载位图资源
	HBITMAP hBmp = LoadBitmap( g_hInst,
		MAKEINTRESOURCE( IDB_BALL01 ) );
	//获取位图的相关信息
	BITMAP bmpInfo = { 0 };
	GetObject( hBmp, sizeof( bmpInfo ), &bmpInfo );
	//创建放置位图的DC
	HDC hBmpDC = CreateCompatibleDC( hDC );
	//将位图放入hBmpDC
	HBITMAP hOldBmp = ( HBITMAP )
		SelectObject( hBmpDC, hBmp );
	//绘制位图
	BitBlt( hDC, 100, 100, bmpInfo.bmWidth,
		bmpInfo.bmHeight, hBmpDC,
		0, 0, SRCCOPY );
	//拉伸绘制
	StretchBlt( hDC, 200, 100, 300, 300,
		hBmpDC, 0, 0, bmpInfo.bmWidth,
		bmpInfo.bmHeight, SRCCOPY );
	//取出位图
	SelectObject( hBmpDC, hOldBmp );
	//删除DC
	DeleteDC( hBmpDC );
	//删除位图
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



