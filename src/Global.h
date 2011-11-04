/***********************************************************************************
 ===================================================================================

*	File name: 		Global.cpp
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Required includes, global methods.

====================================================================================		
************************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "GameWindow.h"
#include <string>
#include <stack>

struct SPRITE;
struct INPUTDATA;
class GameState;

using std::string;
using std::stack;

// libraries
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
//#pragma comment (lib, "dinput.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
	

#pragma comment (lib, "user32.dll")

#define COLLISION_BOUND  10
#define TILE_SIZE 32
#define TILESET_NAME "tilesetsmooth.png"
#define WINDOW_WIDTH 36
#define WINDOW_HEIGHT 24

/*#define WINDOW_WIDTH 18
#define WINDOW_HEIGHT 12*/



// prototypes for...
// Direct3D.cpp
void InitDirect3D(GAMEWINDOW* gw);
void CloseDirect3D();
void CloseDirectInput();
void StartRendering();
void StopRendering();
bool HandleMessages();
void LoadSprite(SPRITE * pSprite, LPCTSTR File, int width, int height, int cols, int rows);
void LoadFont();
void DrawFont(int, int,int,int,string,int);
void DrawFontRed(int, int,int,int,string,int);
void DrawFontBlue(int, int,int,int,string,int);
void DrawFontWhite(int, int,int,int,string,int);
void DrawSprite(SPRITE* pSprite, int frame, float x, float y, float z, float heading);
//DirectInput.cpp
void InitDirectInput(HINSTANCE hInstance, GAMEWINDOW* gw);
void GetKeys(BYTE* KeyState);

//Loop.cpp
void MainLoop();
