// header files
#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameWindow.h"
#include "Sprite.h"

// libraries
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// prototypes for...
// Direct3D.cpp
void InitDirect3D(GAMEWINDOW* gw);
void CloseDirect3D();
void StartRendering();
void StopRendering();
void LoadSprite(SPRITE * pSprite, LPCTSTR File, int width, int height, int cols, int rows)
