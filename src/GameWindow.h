/***********************************************************************************
 ===================================================================================

*	File name: 		GameWindow.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		A convinience struct, used to set the dimensions of the window

====================================================================================		
************************************************************************************/
#pragma once

struct GAMEWINDOW
{
	HWND hWnd;
	int width, height;
	bool windowed;

	GAMEWINDOW()
	{
		hWnd = NULL;
		width = 1152;
		height = 768;
		windowed = true;
	}
};