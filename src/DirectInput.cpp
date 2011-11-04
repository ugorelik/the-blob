/***********************************************************************************
 ===================================================================================

*	File name: 		DirectInput.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description

====================================================================================		
************************************************************************************/

#include "Global.h"
LPDIRECTINPUT8			din;
LPDIRECTINPUTDEVICE8	dinkeyboard;
LPDIRECTINPUTDEVICE8	dinmouse;

void InitDirectInput(HINSTANCE hInstance, GAMEWINDOW* gw)
{
	DirectInput8Create(hInstance,
						DIRECTINPUT_VERSION,
						IID_IDirectInput8,
						(void**)&din,
						NULL);
	din->CreateDevice(GUID_SysKeyboard, &dinkeyboard, NULL);
	din->CreateDevice(GUID_SysMouse, &dinmouse, NULL);

	dinkeyboard->SetDataFormat(&c_dfDIKeyboard);
	dinmouse->SetDataFormat(&c_dfDIMouse);

	dinkeyboard->SetCooperativeLevel(gw->hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	dinmouse->SetCooperativeLevel(gw->hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	dinmouse->Acquire();
	return;
}

void CloseDirectInput(void)
{
	dinkeyboard->Unacquire();
	din->Release();

	return;
}

void GetKeys(BYTE* KeyState){
	dinkeyboard->Acquire();

	dinkeyboard->GetDeviceState(256,(LPVOID)KeyState);

	for(int Index = 0; Index < 256; Index++)
		*(KeyState + Index) &=0x80;
	return;
}