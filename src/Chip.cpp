/***********************************************************************************
 ===================================================================================

*	File name: 		Chip.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		When collided with, the chip pops up a new screen and dissapears 
====================================================================================		
************************************************************************************/
#include "Chip.h"
#include "Player.h"
#include "Game.h"
#include "StoryText.h"

//Chip constructor
Chip::Chip(int x, int y, int id)
	: Entity(x,y)
{
	_frame = 11;
	_type = TYPE_CHIP;
	_id = id;
}

//Collide Action, passes in the player that is colliding with the chip
bool Chip::CollideAction(Player * player)
{
	Game* game = Game::Instance();
	//game->AddProgress();

	stack<GameState *> * stackState = game->GetStackState();
	stackState->push(new StoryText(_id,stackState));
	_toRemove = true;
	return false;
}