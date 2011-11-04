/***********************************************************************************
 ===================================================================================

*	File name: 		WinMain.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description

====================================================================================		
************************************************************************************/
#include "Global.h"
#include "stdio.h"
#include "stdlib.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void DisplayWindow(GAMEWINDOW* gw, HINSTANCE hInstance, int nCmdShow){
	WNDCLASSEX wc;	//struct to hold window class info
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	//fill in the struct with needed info
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass";
	//register the window class
	RegisterClassEx(&wc);
	//create window, pass result to handle
	gw->hWnd = CreateWindowEx(NULL,
						  "WindowClass",	//name of window class
						  "Dr. Rhodes",		//title of window
						  WS_OVERLAPPEDWINDOW,//window style
						  80,		//x position
						  0,		//y position
						  gw->width,		//width
						  gw->height,		//height
						  NULL,
						  NULL,
						  hInstance,
						  NULL);
	//display the window
	ShowWindow(gw->hWnd, nCmdShow);
}

//the main function
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	GAMEWINDOW gw; //handle for the window
	DisplayWindow(&gw, hInstance, nCmdShow);
	//Initialize Direct3D
	InitDirect3D(&gw);
	InitDirectInput(hInstance,&gw);

	//enter the main loop
	MainLoop();

	CloseDirect3D();
	CloseDirectInput();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
			{
				//close the application
				PostQuitMessage(0);
				return 0;
			}break;
	}
	return DefWindowProc (hWnd, message, wParam, lParam);
}

	
// Check for Messages and Handle
bool HandleMessages()
{
    static MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return FALSE;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return TRUE;
}

/*
Added to be able to compile

BOOL WINAPI PeekMessage(
  __out     LPMSG lpMsg,
  __in_opt  HWND hWnd,
  __in      UINT wMsgFilterMin,
  __in      UINT wMsgFilterMax,
  __in      UINT wRemoveMsg
  ){}
	
HCURSOR WINAPI LoadCursor(
  __in_opt  HINSTANCE hInstance,
  __in      LPCTSTR lpCursorName
  ){}

LRESULT WINAPI DispatchMessage(
  __in  const MSG *lpmsg
  ){}

BOOL WINAPI ShowWindow(
  __in  HWND hWnd,
  __in  int nCmdShow
  ){}

LRESULT WINAPI DefWindowProc(
  __in  HWND hWnd,
  __in  UINT Msg,
  __in  WPARAM wParam,
  __in  LPARAM lParam
  ){}

HWND WINAPI CreateWindowEx(
  __in      DWORD dwExStyle,
  __in_opt  LPCTSTR lpClassName,
  __in_opt  LPCTSTR lpWindowName,
  __in      DWORD dwStyle,
  __in      int x,
  __in      int y,
  __in      int nWidth,
  __in      int nHeight,
  __in_opt  HWND hWndParent,
  __in_opt  HMENU hMenu,
  __in_opt  HINSTANCE hInstance,
  __in_opt  LPVOID lpParam
  ){}

BOOL WINAPI TranslateMessage(
  __in  const MSG *lpMsg
  ){}

VOID WINAPI PostQuitMessage(
  __in  int nExitCode
  ){}

ATOM WINAPI RegisterClassEx(
  __in  const WNDCLASSEX *lpwcx
  ){}

  */
