/***********************************************************************************
 ===================================================================================

*	File name: 		Scientist.cpp < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		The Scientist class contains scientist specific movement characteristics.
		All that makes the scientist different from soldiers and zombies.
====================================================================================		
************************************************************************************/
#include "Scientist.h"
#include "Game.h"
#include "Player.h"
// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
Scientist::Scientist() 
{
	_frame = TILE_SCIENTIST;
	_type = TYPE_SCIENTIST;

}

Scientist::Scientist(int x, int y, float heading, int moveDelay, int patDirection, int patLength)
: Entity(x,y,heading, patDirection, patLength, moveDelay)
{
	pos.x = x*TILE_SIZE;
	pos.y = y*TILE_SIZE;
	_heading = heading;
	_frame = TILE_SCIENTIST;
	_type = TYPE_SCIENTIST;
	_deathFrame = TILE_DEAD_SCIENTIST;
	_stepAdd = STEP_SCIENTIST;
}

void Scientist::Update(long time){
	Entity::Update(time);
	RunAI(time);
}

void Scientist::RunAI(int time){
	Game* game = Game::Instance();
	static int lastSeenTime = time;
	if (game->GetPlayer()->GetState()==STATE_BLOB){
		if (Entity::CheckLineOfSight(pos.x/TILE_SIZE, pos.y/TILE_SIZE))
		{
			aiState = 1;
		}
	}
	if (aiState == 1)
	{
		Flee(time);
	}
	else if(aiState == 2)
		Patrol(time);
	else if (aiState == 3)
		Search(time);

	
	return;
}



bool Scientist::CollideAction(Player * player)
{
	Entity::CollideAction(player);

	return true;
}