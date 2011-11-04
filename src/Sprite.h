/***********************************************************************************
 ===================================================================================

*	File name: 		Sprite.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Sprite wrapper

====================================================================================		
************************************************************************************/
#pragma once

#include "Global.h"

struct SPRITE
{
    int rows, cols;    // number of rows and columns
    int width, height;    // width and height of each frame
    LPDIRECT3DTEXTURE9 tex;    // texture
};