/***********************************************************************************
 ===================================================================================

*	File name: 		Direct3D.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description: Wrapper for DirectX.

====================================================================================		
************************************************************************************/

#include "Global.h"
#include "Sprite.h"


#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
D3DPRESENT_PARAMETERS d3dpp;
LPD3DXSPRITE d3dspt;
LPD3DXFONT dxfont;    // the pointer to the font object

//Create the Direct3D and the Direct3D Device
void InitDirect3D(GAMEWINDOW* gw){
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.Windowed = gw->windowed;
	d3dpp.BackBufferWidth = gw->width;
	d3dpp.BackBufferHeight = gw->height;
	//initialize d3ddev
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      gw->hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
	//inititalize the sprite
	D3DXCreateSprite(d3ddev,&d3dspt);
    return;
}
//Close stuff down
void CloseDirect3D() {
	d3ddev->Release();
	d3d->Release();

	return;
}

void StartRendering(){
	d3ddev->Clear(0,NULL,D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f,0);
	d3ddev->BeginScene();
	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);
	return;
}

void StopRendering(){
	d3dspt->End();
	d3ddev->EndScene();
	d3ddev->Present(NULL,NULL,NULL,NULL);
	return;
}


void LoadFont() {

//	string theFont = "Arial";
	string theFont = "Courier New";

	    D3DXCreateFont(d3ddev,						// the D3D Device
                   30,								// font height of 30
                   0,								// default font width
                   FW_BOLD,						// font weight
                   1,								// not using MipLevels
                   false,							//	 italic font
                   DEFAULT_CHARSET,					// default character set
                   OUT_DEFAULT_PRECIS,				// default OutputPrecision,
                   DEFAULT_QUALITY,					// default Quality
                   DEFAULT_PITCH | FF_DONTCARE,	    // default pitch and family
				   theFont.c_str(),					// use Facename Arial
                   &dxfont);						// the font object
}



void DrawFont(int xPos, int yPos, int width, int height, const string theString, int length)
{
	// create a RECT to contain the text
    static RECT textbox; 
	SetRect(&textbox, xPos, yPos, width, height); 
	
	D3DXVECTOR3 position(xPos,yPos,0); // Get the position in a VECTOR3
	D3DXMATRIX matTranslateOriginal; 
	D3DXMatrixTranslation(&matTranslateOriginal, xPos + TILE_SIZE/2, yPos +TILE_SIZE/2 , 0);
	d3dspt->SetTransform(&matTranslateOriginal); // Set's the transformation matrix

    // draw the Hello World text
    dxfont->DrawTextA(d3dspt,
					  theString.c_str(),
                      length,
                      &textbox,
                      DT_LEFT, // TODO: Change this from center
                      D3DCOLOR_ARGB(255, 0, 0, 0));
}


void DrawFontWhite(int xPos, int yPos, int width, int height, const string theString, int length)
{
	// create a RECT to contain the text
    static RECT textbox; 
	SetRect(&textbox, xPos, yPos, width, height); 
	
	D3DXVECTOR3 position(xPos,yPos,0); // Get the position in a VECTOR3
	D3DXMATRIX matTranslateOriginal; 
	D3DXMatrixTranslation(&matTranslateOriginal, xPos + TILE_SIZE/2, yPos +TILE_SIZE/2 , 0);
	d3dspt->SetTransform(&matTranslateOriginal); // Set's the transformation matrix

    // draw the Hello World text
    dxfont->DrawTextA(d3dspt,
					  theString.c_str(),
                      length,
                      &textbox,
                      DT_LEFT,
                      D3DCOLOR_ARGB(255, 255, 255, 255));
}

void DrawFontRed(int xPos, int yPos, int width, int height, const string theString, int length)
{
	// create a RECT to contain the text
    static RECT textbox; 
	SetRect(&textbox, xPos, yPos, width, height); 
	
	D3DXVECTOR3 position(xPos,yPos,0); // Get the position in a VECTOR3
	D3DXMATRIX matTranslateOriginal; 
	D3DXMatrixTranslation(&matTranslateOriginal, xPos + TILE_SIZE/2, yPos +TILE_SIZE/2 , 0);
	d3dspt->SetTransform(&matTranslateOriginal); // Set's the transformation matrix

    // draw the Hello World text
    dxfont->DrawTextA(d3dspt,
					  theString.c_str(),
                      length,
                      &textbox,
                      DT_LEFT,
                      D3DCOLOR_ARGB(255, 255, 0, 0));
}

void DrawFontBlue(int xPos, int yPos, int width, int height, const string theString, int length)
{
	// create a RECT to contain the text
    static RECT textbox; 
	SetRect(&textbox, xPos, yPos, width, height); 
	
	D3DXVECTOR3 position(xPos,yPos,0); // Get the position in a VECTOR3
	D3DXMATRIX matTranslateOriginal; 
	D3DXMatrixTranslation(&matTranslateOriginal, xPos + TILE_SIZE/2, yPos +TILE_SIZE/2 , 0);
	d3dspt->SetTransform(&matTranslateOriginal); // Set's the transformation matrix

    // draw the Hello World text
    dxfont->DrawTextA(d3dspt,
					  theString.c_str(),
                      length,
                      &textbox,
                      DT_LEFT,
                      D3DCOLOR_ARGB(255, 0, 100, 255));
}


void LoadSprite(SPRITE * pSprite, LPCTSTR File, int width, int height, int cols, int rows)
{
	D3DXCreateTextureFromFileEx(d3ddev,
                                File,
                                D3DX_DEFAULT,
                                D3DX_DEFAULT,
                                D3DX_DEFAULT,
                                NULL,
                                D3DFMT_A8R8G8B8,
                                D3DPOOL_MANAGED,
                                D3DX_DEFAULT,
                                D3DX_DEFAULT,
                                D3DCOLOR_XRGB(255, 0, 255),
                                NULL,
                                NULL,
                                &pSprite->tex);
	pSprite->width= width;
	pSprite->height = height;
	pSprite->cols = cols;
	pSprite->rows = rows;

	return;
}

void DrawSprite(SPRITE* pSprite, int frame, float x, float y, float z, float heading)
{
	RECT FrameBox;
	FrameBox.left = (frame % pSprite ->cols) * pSprite->width;
	FrameBox.top = (frame / pSprite->rows) * pSprite->height; // was / changed to %
	FrameBox.right = FrameBox.left + pSprite->width;
	FrameBox.bottom = FrameBox.top + pSprite->height;



	D3DXVECTOR3 position(x,y,z); // Get the position in a VECTOR3

	D3DXMATRIX matTransform, matRotate, matTranslate, matTranslateOriginal; 
	
	// Do rotations
	D3DXMatrixTranslation( &matTranslate, (-x) - TILE_SIZE/2, (-y) -TILE_SIZE/2, 1.0f );
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(heading));
	D3DXMatrixTranslation(&matTranslateOriginal, x + TILE_SIZE/2, y +TILE_SIZE/2 , 0);

	
	// Make transformation matrix
	matTransform = matTranslate * matRotate * matTranslateOriginal;

	d3dspt->SetTransform(&matTransform); // Set's the transformation matrix
	
	d3dspt->Draw(pSprite->tex,&FrameBox, NULL, &position, D3DCOLOR_XRGB(255,255,255));

	return;
}
