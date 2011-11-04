/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///		Filename: Entity.cpp																								  ///
///		Author: Michael Anderson 11/02																						  ///
///		Summary: Implements the Entity Class																				  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameObject.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"

// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
Entity::Entity()
{
	_lastMove = 0;
	_moveAmountX = 0;
	_moveAmountY = 0;
}


Entity::Entity(int x, int y)
: GameObject(x,y)
{
	_lastMove = 0;
	_moveAmountX = 0;
	_moveAmountY = 0;
}


Entity::Entity(int x, int y, int frame)
: GameObject(x,y,frame)
{
	_lastMove = 0;
	_moveAmountX = 0;
	_moveAmountY = 0;
}

Entity::Entity(int x, int y, int frame, float heading)
: GameObject(x,y,frame, heading)
{
	_lastMove = 0;
	_moveAmountX = 0;
	_moveAmountY = 0;
}

Entity::Entity(int x, int y, float heading, int patDirection, int patLength, int moveDelay)
: GameObject(x,y, heading), _patDirection(patDirection),_patLength(patLength), _moveDelay(moveDelay) 
{
	_lastMove = 0;
	_stepsMoved = 0;
	aiState = 2;
	_moveAmountX = 0;
	_moveAmountY = 0;
}

// ------------------------------------------------------------------------------------------------------------
// Methods
// ------------------------------------------------------------------------------------------------------------
void Entity::Update(long time)
{
	// ---------------------------------------------------
	// The new Block Move for enties
	if (_moveAmountX != 0)
	{
		if (_moveAmountX < 0)
		{
			pos.x -= vel.x;
			_moveAmountX += vel.x;
		}
		else 
		{
			pos.x += vel.x;
			_moveAmountX -= vel.x;
		}
	}
	else if (_moveAmountX == 0){
		vel.x = 0;
		//ApproximateBlock();
	}
	if (_moveAmountY !=0)
	{
		if (_moveAmountY < 0)
		{
			pos.y -= vel.y;
			_moveAmountY += vel.y;
		}
		else 
		{
			pos.y += vel.y;
			_moveAmountY -= vel.y;
		}
	}
	else if (_moveAmountY == 0){
		vel.y = 0;
		//ApproximateBlock();
	}
	//end Block Move (int)
	
}



// ------------------------------------------------------------------------------------------------------------
// AI Methods
// ------------------------------------------------------------------------------------------------------------
void Entity::Chase(int time){
	Game* game = Game::Instance();
	static int lastSeenTime = time;
	int diffx = pos.x - game->GetPlayer()->pos.x;
	int diffy = pos.y - game->GetPlayer()->pos.y;
	int tempx;
	int tempy;
	//GET ABSOLUTE
	if (diffx < 0)
		tempx = diffx*(-1);
	else
		tempx = diffx;
	if (diffy < 0)
		tempy = diffy*(-1);
	else
		tempy = diffy;
			
	bool closeto = false;
			
	if (tempx < 192 && tempy < 192)
		closeto = true;
	else
		closeto = false;

	// Timer or in Line of sight
	if (closeto || time - lastSeenTime < 3000)
	{

		if (tempx < tempy)
		{
			//Y position is closer
			if (diffy > 0)
				BlockMove(DIRECTION_UP);
			else
				BlockMove(DIRECTION_DOWN);
		}
		else
		{
			//X POSITION is closer
			if (diffx > 0)
				BlockMove(DIRECTION_LEFT);
			else
				BlockMove(DIRECTION_RIGHT);
		}
	}
	else
	{
		Entity::ApproximateBlock();
		aiState = 3;
	}
}

void Entity::Flee(int time){
	Game* game = Game::Instance();
	static int lastSeenTime = time;
	int diffx = pos.x - game->GetPlayer()->pos.x;
	int diffy = pos.y - game->GetPlayer()->pos.y;
	int tempx;
	int tempy;
	//GET ABSOLUTE
	if (diffx < 0)
		tempx = diffx*(-1);
	else
		tempx = diffx;
	if (diffy < 0)
		tempy = diffy*(-1);
	else
		tempy = diffy;
			
	bool closeto = false;
			
	if (tempx < 192 && tempy < 192)
		closeto = true;
	else
		closeto = false;

	// Timer or in Line of sight
	if (closeto || time - lastSeenTime < 3000)
	{

		if (tempx < tempy)
		{
			//Y position is closer
			if (diffy < 0)
				BlockMove(DIRECTION_UP);
			else
				BlockMove(DIRECTION_DOWN);
		}
		else
		{
			//X POSITION is closer
			if (diffx < 0)
				BlockMove(DIRECTION_LEFT);
			else
				BlockMove(DIRECTION_RIGHT);
		}
	}
	else
	{
		aiState = 3;
		Entity::ApproximateBlock();
	}
}

void Entity::Patrol(int time){
	if( (time - _lastMove) > _moveDelay){
			_lastMove = time;
			if (_stepsMoved >= _patLength){
				_stepsMoved = 0;
				_patDirection = -_patDirection;
			}
			else if ((vel.x == 0) && (vel.y ==0)){
				_stepsMoved++;
				BlockMove(_patDirection);
			}
		}
}

void Entity::Search(int time){
	if((time- _lastMove) > _moveDelay)
		{
			_lastMove = time;
			_heading  =  (int)(_heading+90)%360;
		}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *		LINE OF SIGHT
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool Entity::CheckLOS(int x, int y, int direction, int sight){
	if(sight == 0)
		return false;
	Game * game = Game::Instance();
	//is this square occupied by THE BLOB
		//if so, return true
	//if( game->GetPlayer()->GetPosition().x >= x-1 && game->GetPlayer()->GetPosition().x <= x &&
		//game->GetPlayer()->GetPosition().y >= y-1 && game->GetPlayer()->GetPosition().y <= y )
		 
	D3DXVECTOR2 playerPos = game->GetPlayer()->GetPosition();
	int playerX = playerPos.x;
	int playerY = playerPos.y;


	switch (direction)
	{
	case 0 :
		if (playerX == x && playerY == y - 1) return true;
			else CheckLOS(x,y-1,0,sight-1);
		break;

	case 1 :

		if (playerPos.x == x + 1 && playerPos.y == y) return true;
		else	CheckLOS(x+1,y,1,sight-1);
		break;

	case 2 :
		if (playerPos.x == x && playerPos.y == y + 1) return true;
		else	CheckLOS(x,y+1,2,sight-1);
		break;

	case 3 :
		if (playerPos.x == x - 1 && playerPos.y == y) return true;
			else CheckLOS(x-1,y,3,sight-1);
		break;
	}
}

bool Entity::CheckLineOfSight(int x, int y)
{
	Game * game = Game::Instance();

	int playerX = game->GetPlayer()->GetPosition().x;
	int playerY = game->GetPlayer()->GetPosition().y;

		switch ((int)_heading/90)
		{
		case 0 :
			if (playerY >= y - 4 && playerY <= y && playerX == x) 
				return true;
			break;

		case 1 :

			if (playerX >= x + 1 && playerX <= x + 4 && playerY == y) return true;

		break;

		case 2 :
			if (playerY >= y + 1 && playerY <= y + 4 && playerX == x) 
				return true;

		break;

		case 3 :
			if (playerX>= x - 4 && playerX<= x && playerY == y) return true;
		break;

		}
		return false;

}


bool Entity::CheckDirectionInvalid(int checkLoc)
{
	Game * game = Game::Instance();

	D3DXVECTOR2 checkPos = GameObject::GetRelativePostion();
	switch (checkLoc)
	{
	// Up
	case DIRECTION_UP:
		_heading  = 0;
		checkPos.y = checkPos.y - 1;
		break;
	// Down
	case DIRECTION_DOWN:
		_heading  = 180;
		checkPos.y = checkPos.y + 1;
		break;
	// Left
	case DIRECTION_LEFT:
		_heading  = 270;
		checkPos.x = checkPos.x - 1;
		break;
	// Right
	case DIRECTION_RIGHT:
		_heading  = 90;
		checkPos.x = checkPos.x + 1;
		break;
	}

	Entity * curr;
	vector<Entity *>::iterator itr;
	// Check the entity list
	for (itr = game->GetEntityList()->begin(); itr != game->GetEntityList()->end(); ++itr)
	{
		curr = *itr;
		if (curr->GetRelativePostion() == checkPos)
		{
			return true;
		}
	}

	// Check the enemy list
	for (itr = game->GetEnemyList()->begin(); itr != game->GetEnemyList()->end(); ++itr)
	{
		curr = *itr;
		if (curr->GetRelativePostion() == checkPos && curr->GetType() != TYPE_CHIP)
		{
			return true;
		}
	}

	return false;
}

void Entity::BlockMove(int moveDirection)
{
	// Check if it's already moving
	if (_moveAmountX != 0 || _moveAmountY!= 0) return;

	// Check if it's a valid direction
	if (CheckDirectionInvalid(moveDirection)) return;

	switch (moveDirection)
	{
		case DIRECTION_UP :
					_heading = 0.0f;
					_moveAmountY = -TILE_SIZE;
					vel.y = 2;
				break;

		case DIRECTION_LEFT :
					_heading = 270.0f;
					_moveAmountX = -TILE_SIZE;
					vel.x = 2;
				break;

		case DIRECTION_RIGHT :
					_heading = 90.0f;
					_moveAmountX = TILE_SIZE;
					vel.x = 2;
				break;

		case DIRECTION_DOWN :
					_heading = 180.0f;
					_moveAmountY = TILE_SIZE;
					vel.y = 2;
				break;
	}
}

void Entity::ApproximateBlock()
{
	int x = pos.x / TILE_SIZE;
	x *= TILE_SIZE;

	int y = pos.y / TILE_SIZE;
	y*= TILE_SIZE;

	pos.x = x;
	pos.y = y;
	_moveAmountX = 0;
	_moveAmountY = 0;
	vel.x = 0;
	vel.y = 0;
}

bool Entity::CollideAction(Player * player)
{
	int speedModifier = 2;
	player->pos -= player->vel;

	int x = player->pos.x;
	int y = player->pos.y;

	if( (x+TILE_SIZE-pos.x < 10) &&  (x+TILE_SIZE-pos.x > 0) )
		player->vel.x =  player->vel.x / -speedModifier;
	if( (pos.x+TILE_SIZE-x < 10) && (pos.x+TILE_SIZE-x > 0) )
		player->vel.x =  player->vel.x / -speedModifier;

	if( (y+TILE_SIZE-pos.y < 10) &&  (y+TILE_SIZE-pos.y > 0) )
		player->vel.y =  player->vel.y / -speedModifier;
	if( (pos.y+TILE_SIZE-y < 10) && (pos.y+TILE_SIZE-y > 0) )
		player->vel.y =  player->vel.y / -speedModifier;


	return false;
}

int Entity::GetType() { return _type; }
int Entity::GetStepAdd() { return _stepAdd; }
int Entity::GetDeathFrame() { return _deathFrame; }