/***********************************************************************************
 ===================================================================================

*	File name: 		TutorialChip.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Specific type of chip
====================================================================================		
************************************************************************************/
#include "TutorialChip.h"
#include "Player.h"
#include "Game.h"
#include "StoryText.h"

TutorialChip::TutorialChip(int x, int y, int id)
	: Entity(x,y)
{
	_frame = 39;
	_type = TYPE_CHIP;
	_id = id;
}

bool TutorialChip::CollideAction(Player * player)
{
	Game* game = Game::Instance();
	//game->AddProgress();

	stack<GameState *> * stackState = game->GetStackState();
	stackState->push(new StoryText(_id,stackState));
	_toRemove = true;
	return false;
}