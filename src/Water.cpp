/***********************************************************************************
 ===================================================================================

*	File name: 		Water.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Alters the player's move speed
====================================================================================		
************************************************************************************/
#include "Water.h"
#include "Player.h"
#include "Game.h"

Water::Water(int x, int y, int id)
	: Entity(x,y)
{
	_frame = 38;
	_type = 4;
	_id = id;
}

bool Water::CollideAction(Player * player)
{
	if (player->GetState() == STATE_BLOB) {
		player->vel.x *= .95;
		player->vel.y *= .95;
	}
	return false;
}