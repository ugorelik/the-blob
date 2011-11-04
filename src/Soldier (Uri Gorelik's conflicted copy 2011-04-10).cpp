
#include "Soldier.h"
#include "Game.h"
#include "Player.h"


// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
Soldier::Soldier() 
{
	_frame = TILE_SOLDIER;
	_type = TYPE_SOLDIER;
	_chase = false;
	//aiState = 2;
}

Soldier::Soldier(int x, int y, float heading)
: Entity(x,y,heading, DIRECTION_RIGHT, 0, 8000000)
{
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	vel.x = 0;
	vel.y = 0;
	defaultPos = pos;
	aiState = 2;
	_moved = false;
	_lastMove = 0;
	_heading = heading;
	_frame = TILE_SOLDIER;
	_type = TYPE_SOLDIER;
	_deathFrame = TILE_DEAD_SOLDIER;
	_stepAdd = STEP_SOLDIER;
}

Soldier::Soldier(int x, int y, float heading, int moveDelay = 8000000, int patDirection = 0 , int patLength = 0)
: Entity(x,y,heading, patDirection, patLength, moveDelay)
{
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	vel.x = 0;
	vel.y = 0;
	defaultPos = pos;
	aiState = 2;
	_moved = false;
	_lastMove = 0;
	_heading = heading;
	_frame = TILE_SOLDIER;
	_type = TYPE_SOLDIER;
	_deathFrame = TILE_DEAD_SOLDIER;
	_stepAdd = STEP_SOLDIER;
}

void Soldier::Update(long time){
	Entity::Update(time);
	RunAI(time);
}

void Soldier::RunAI(int time){
	Game* game = Game::Instance();
	
	//check to see if the blob is in sight. this is the highest priority behaviour
	if (game->GetPlayer()->GetState()==STATE_BLOB){
		if (Entity::CheckLineOfSight(pos.x/TILE_SIZE, pos.y/TILE_SIZE))
		{
			aiState = 1;
		}
	}

	//this is the chase state
	if(aiState == 1)
	{
		Chase(time);
	}
	if (aiState == 2){
		if( (time - _lastMove) > _moveDelay){
			_lastMove = time;
			if ((vel.x == 0) && (_moved == false)){
				BlockMove(_patDirection);
				_moved = true;
			}
			else if ((vel.x == 0) && (_moved == true)){
				BlockMove(-_patDirection);
				_moved = false;
			}//*/
		}

	}//post chased, confused searching behaviour
	else if (aiState == 3){
		if((time- _lastMove) > _moveDelay)
		{
			_lastMove = time;
			_heading  =  (int)(_heading+90)%270;
		}
	}
	return;
}



bool Soldier::CollideAction(Player * player)
{
	Entity::CollideAction(player);


	aiState = 3;
	return true;
}