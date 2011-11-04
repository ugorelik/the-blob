/***********************************************************************************
 ===================================================================================

*	File name: 		Zombie.cpp < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Zombie code that details its AI and movement characteristics as well as
		collision event.
====================================================================================		
************************************************************************************/
#include "Zombie.h"
#include "Game.h"
#include "Player.h"


// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
Zombie::Zombie() 
{
	_frame = 5;
}

Zombie::Zombie(int x, int y, float heading, int moveDelay, int patDirection, int patLength)
: Entity(x,y,heading, patDirection, patLength, moveDelay)
{
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	defaultPos = pos;
	_heading = heading;
	_frame = TILE_ZOMBIE;
	//_type = TYPE_ZOMBIE;
	_deathFrame = TILE_DEAD_ZOMBIE;
	_scentRadius = 75;
}

void Zombie::Update(long time){
	Entity::Update(time);
	RunAI(time);
}

bool Zombie::ZombieLOS(){
	Game* game = Game::Instance();
	int playerX = game->GetPlayer()->pos.x + TILE_SIZE/2;
	int playerY = game->GetPlayer()->pos.y + TILE_SIZE/2;

	int zombieX = pos.x + TILE_SIZE/2;
	int zombieY = pos.y + TILE_SIZE/2;

	if( ((playerX-zombieX)*(playerX-zombieX) + (playerY-zombieY)*(playerY-zombieY)) < _scentRadius*_scentRadius )
		return true;

	return false;
}

void Zombie::RunAI(int time){
	Game* game = Game::Instance();
	if (ZombieLOS())
	{
		aiState = 1;
	}
	if (aiState == 1)
	{
		Chase(time);
	}
	if(aiState == 2)
		Patrol(time);
	return;
}



bool Zombie::CollideAction(Player * player)
{
	Entity::CollideAction(player);

	switch (player->GetState() )
	{
	case STATE_SCIENTIST:
	case STATE_BLOB :
		player->vel.x = 0;
		player->vel.y = 0;
		return true;
		break;
	case STATE_SOLDIER :
		_toRemove = true;
		return false;
		break;
	}

	
	player->vel.x = 0;
	player->vel.y = 0;

	return false;
}