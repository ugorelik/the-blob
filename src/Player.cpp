/***********************************************************************************
 ===================================================================================

*	File name: 		Player.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		The player class controls all of the user's actions and interaction with
		the game as a sprite.
====================================================================================		
************************************************************************************/

#include "Global.h"
#include "Player.h"
#include "Entity.h"
#include "InputData.h"
#include "Game.h"
#include "Level.h"
#include "TutorialMenu.h"

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Player::Player(int x, int y, Game * game)
	: ACCELERATION(0.075), _frame(TILE_BLOB), _state(0)
{
	SetPosition(x,y);
	_stepCounter = 0;
	_theGame = game;
	_readyToPossess = false;
	_accumulatedPossessTime = 0;
}


// --------------------------------------------------------------------------
// Main update functions
// --------------------------------------------------------------------------
void Player::Update(long time, INPUTDATA * input)
{

	if (input->ESC)
	{
		GetGame()->GetStackState()->push (new TutorialMenu( GetGame()->GetStackState()) );
	}

	// This is used to handle addition keys
	// TODO: Change it so we're not using the debug mode in release
	DebugMode(input);

	// Update based on state
	if ( _state == STATE_SOLDIER ) {
		// Soldier sate	
		BlockMove(input);

		if (input->kill)
			_stepCounter = 0;
	} 

	else if (_state == STATE_SCIENTIST ) {
		BlockMove(input);

		if (input->kill)
			_stepCounter = 0;
	}

	else {
		// Normal blob movement
		UpdateVelocity(input);

		// Check if the player is trying to possess something
		if (input->possess){
			// Change the frame to the posses frame
			_frame = TILE_BLOB_POSSESS;

			// If the player has held down space long enough
			if (_readyToPossess)
				Possess(input);

		} else if (!input->possess && _state == STATE_BLOB) {
			_frame = TILE_BLOB;
			_accumulatedPossessTime = 0;
			_readyToPossess = false;
		}
	}

	// Can't possess anymore
	if (_state != STATE_BLOB && _stepCounter == 0)
	{

		Game * game = Game::Instance();

		int deathFrame = 0;
		switch (_state)
		{
		case STATE_SOLDIER :
				deathFrame = TILE_DEAD_SOLDIER;
			break;
		case STATE_SCIENTIST :
				deathFrame = TILE_DEAD_SCIENTIST;
			break;

		}
		// Add a death frame
		game->GetCurrentLevel()->GetResetList()->push_back(new GameObject( (pos.x + TILE_SIZE/2)/TILE_SIZE,(pos.y + TILE_SIZE/2)/TILE_SIZE, deathFrame)); // Same issue as level trans
		ResetToPlayer();
	}

	// Add to the accumulated time

	if (input->possess) 
	{
		if (_accumulatedPossessTime == 0) {
			_accumulatedPossessTime = time;
		}
		if (time - _accumulatedPossessTime > 479) {
			_readyToPossess = true;

			if (_state == STATE_BLOB)
				_frame = TILE_BLOB_POSSESS_READY;
		}
	}
	

	// Check for level trans
	CheckTransition();
}


// --------------------------------------------------------------------------
// POSSESS
// --------------------------------------------------------------------------
void Player::Possess(INPUTDATA * input)
{


	// Player needs the list of entities
	Game * game = Game::Instance();

	D3DXVECTOR2 targetPos = GetApproximatePosition();
	D3DXVECTOR2 targetFinalPos;

	int theHeading = (int)_heading;

	switch (theHeading)
	{
		case 0 :
			targetPos.y = targetPos.y - 1;
			break;
		case 90:
			targetPos.x = targetPos.x + 1;
			break;
		case 180 :
			targetPos.y = targetPos.y + 1;
			break;
		case 270 :
			targetPos.x = targetPos.x - 1;
			break;
	}

	// At this point we have the targets position based on which way the blob is facing.
	// Now we loop through the game entites and check if something that is a soldier
	// or scientist is there

	Entity * target = 0;		// This is the potential candidate

	vector<Entity *> * theList = game->GetCurrentLevel()->GetEnemyList();
	vector<Entity *>::iterator itr;
	for (itr = theList->begin(); itr != theList->end(); ++itr)
	{
		Entity* curr = *itr;
		D3DXVECTOR2 currentPos = curr->GetRelativePostion(); // This is done because we are comparing a Vector2 with a Vector3

		if (currentPos.x == targetPos.x && currentPos.y == targetPos.y && curr->GetHeading() == theHeading)
		{
			target = curr;
			break;
		}
	}

	// We check if we found something
 	if (target == 0) return;

	// We now have a target let's clear the input
	input->Clear();

	// Avoid a glitch
/* 	vel.y = 0;
	vel.x = 0;
	_moveAmountX = 0;
	_moveAmountY = 0;*/

	if (target->GetType() == TYPE_SOLDIER)
	{
		_frame = TILE_SOLDIER;
		_state = STATE_SOLDIER;
	}

	else if (target->GetType() == TYPE_SCIENTIST)
	{
		_frame = TILE_SCIENTIST;
		_state = STATE_SCIENTIST;

	} else return;

	theList->erase(itr); // Can be changed by calling a SetRemoveFlag method
	_stepCounter = target->GetStepAdd();		// Set the amount of steps the player can move
	
	ApproximatePosition(targetPos.x, targetPos.y);
}


// --------------------------------------------------------------------------
// MAIN MOVE
// Update the velocity of the player - dependant on keyboard input
// --------------------------------------------------------------------------
void Player::UpdateVelocity(INPUTDATA * input)
{
	if (!input->possess) 
	{
		if(input->moveUp) {
			_heading = 0.0f;
			if (vel.y > -MAX_SPEED )
				vel.y-=ACCELERATION;
		}
		else if(input->moveDown) {
			_heading = 180.0f;
			if (vel.y < MAX_SPEED) 
				vel.y+=ACCELERATION;
		}
		else
		{
			vel.y*=.99;
		}

		if(input->moveLeft) {
			_heading = 270.0f;
			if (vel.x > -MAX_SPEED)
				vel.x-=ACCELERATION;
		}
		else if(input->moveRight) {
			_heading = 90.f;
			if (vel.x < MAX_SPEED)
				vel.x+=ACCELERATION;
		}
		else
		{
			vel.x*=.99;
		}
	} 

	else // The player is holding down space bar
	{
		if(input->moveUp) {
			_heading = 0.0f;
			
		}
		else if(input->moveDown)
		{
			_heading = 180.0f;
			
		}
		else
		{
			vel.y*=.99;
		}

		if(input->moveLeft) {
			_heading = 270.0f;
		}

		else if(input->moveRight) {
			_heading = 90.f;
		}
		else
		{
			vel.x*=.99;
		}
	}
	

	// Update the position based on the velocity
	pos.x+=vel.x;
	pos.y+=vel.y;
}


// --------------------------------------------------------------------------
// Possession Move
// --------------------------------------------------------------------------

// The speed has to be a multiple of 64 or else it won't work
void Player::BlockMove(INPUTDATA * input)
{

	// Decide the speed
	int speed = 0;
	switch (_state)
	{
		case STATE_SOLDIER :
			speed = BLOCK_MOVE_SOLDIER;
			break;
		case STATE_SCIENTIST :
			speed = BLOCK_MOVE_SCIENTIST;
			break;
	}

	// Check if we can move there
	int dirCheck = InputDataToInt(input);
	if (CheckDirectionInvalid(dirCheck)) return;

	// Which way are we moving
	if (_moveAmountX == 0 && _moveAmountY ==0)
	{
		if(input->moveUp) {
			_heading = 0.0f;
			_moveAmountY = -TILE_SIZE;
						// Dec the step counter
			_stepCounter--;
		}
		else if(input->moveDown) {
			_heading = 180.0f;
			_moveAmountY = TILE_SIZE;
						// Dec the step counter
			_stepCounter--;
		}
		else if(input->moveLeft) {
			_heading = 270.0f;
			_moveAmountX = -TILE_SIZE;		
						// Dec the step counter
			_stepCounter--;
		}
		else if(input->moveRight) {
			_heading = 90.0f;
			_moveAmountX = TILE_SIZE;
						// Dec the step counter
			_stepCounter--;
		}


	}

	// Move EXACTLY 64 units
	if (_moveAmountX != 0)
	{
		if (_moveAmountX < 0)
		{
			pos.x -= speed;
			_moveAmountX += speed;
		}
		else 
		{
			pos.x += speed;
			_moveAmountX -= speed;
		}
	} 

	else if (_moveAmountY !=0)
	{
		if (_moveAmountY < 0)
		{
			pos.y -= speed;
			_moveAmountY += speed;
		}
		else 
		{
			pos.y += speed;
			_moveAmountY -= speed;
		}
	}

	// TODO: This might have to do with the Jiggle
	//if (moveAmountX == 0 || moveAmountY == 0) {
	//	ApproximateBlock();
	//}


}

// --------------------------------------------------------------------------
// HELPER METHODS
// --------------------------------------------------------------------------


// When the player possesses an enemy he needs to be tethered to the grid

int Player::InputDataToInt(INPUTDATA * input) 
{
	if (input->moveUp) return DIRECTION_UP;
	if (input->moveDown) return DIRECTION_DOWN;
	if (input->moveLeft) return DIRECTION_LEFT;
	if (input->moveRight) return DIRECTION_RIGHT;
}

// TODO: This could have something to do with the jiggle
//Approximate the player's position to the nearest block
void Player::ApproximateBlock()
{
	vel.x = 0;
	vel.y = 0;

	int x = pos.x / TILE_SIZE;
	x *= TILE_SIZE;

	int y = pos.y / TILE_SIZE;
	y*= TILE_SIZE;


	pos.x = x;
	pos.y = y;
}

//Approximates the players position based on grid coordinates
void Player::ApproximatePosition(int theX, int theY)
{
	theX *= TILE_SIZE;
	theY *= TILE_SIZE;

	_moveAmountX = 0;
	_moveAmountY = 0;
	vel.x = 0;
	vel.y = 0;
	pos.x = theX;
	pos.y = theY;

//	ApproximateBlock(); //DEBUG
	
}

//Returns the position on the grid
D3DXVECTOR2 Player::GetApproximatePosition()
{

	int x = 0;
	int y = 0;

	x = (pos.x + TILE_SIZE/2) / TILE_SIZE;
	y = (pos.y + TILE_SIZE/2) / TILE_SIZE;
	

	return D3DXVECTOR2(x,y);
}

//Transition method, when the player exits current screen, loads next level
void Player::CheckTransition()
{
	Game * game = Game::Instance();
	if (pos.x > WINDOW_WIDTH * TILE_SIZE || pos.x < -TILE_SIZE
		 || pos.y > WINDOW_HEIGHT * TILE_SIZE || pos.y < -TILE_SIZE)
	{
			//Determine if The level is complete
		int listSize2 = game->GetCurrentLevel()->GetEnemyList()->size();
		Entity * curr2;
		bool wasdone = false;
		if (game->GetCurrentLevel()->_isComplete()) //level was previously is already done
			wasdone = true;
		game->GetCurrentLevel()->setComplete(true);

		for(int i = 0; i < listSize2; i++)
		{	//the player itself is element 0, which is why we start at 1
		
			curr2 =  game->GetCurrentLevel()->GetEnemyList()->at(i);
			if (curr2->GetType() == 3)
			{
				game->GetCurrentLevel()->setComplete(false);
			}
		}
		if (game->GetCurrentLevel()->_isComplete() && !wasdone)
		{												//previous level is complete, add to completion
			game->AddProgress();
		}
	}


	//LEVEL 1 TRANSITIONS
	//RIGHT
	if (pos.x > WINDOW_WIDTH * TILE_SIZE && game->GetCurrentLevelNumber() == 1)
	{
		game->SetLevel(3);
		game->GetPlayer()->SetPosition(0,3);
		game->GetCurrentLevel()->SetDefaultPosition(0,3);
		//LoadSprite(TILE_BLOB, TEXT("Blob64.png"), 64,64,1,1);
	}
	//LEFT
	else if (pos.x < -TILE_SIZE && game->GetCurrentLevelNumber() == 1)
	{
		game->SetLevel(2);
		game->GetPlayer()->SetPosition(35,3);
		game->GetCurrentLevel()->SetDefaultPosition(35,3);
	}
	//DOWN
	else if (pos.y > WINDOW_HEIGHT * TILE_SIZE && game->GetCurrentLevelNumber() == 1)
	{
		game->SetLevel(4);
		game->GetPlayer()->SetPosition(15,0);
		game->GetCurrentLevel()->SetDefaultPosition(15,0);
	}
	//UP
	else if (pos.y < -TILE_SIZE && game->GetCurrentLevelNumber() == 1)
	{
		game->SetLevel(6);
		game->GetPlayer()->SetPosition(15,23);
		game->GetCurrentLevel()->SetDefaultPosition(15,23);
	}
	//LEVEL 2 TRANSITTIONS
	//LEFT
	else if (pos.x < -TILE_SIZE  && game->GetCurrentLevelNumber() == 3) {
		game->SetLevel(1);
		game->GetPlayer()->SetPosition(35,3);
		game->GetCurrentLevel()->SetDefaultPosition(35,3);
	}
	//DOWN
	else if (pos.y > WINDOW_HEIGHT * TILE_SIZE && game->GetCurrentLevelNumber() == 3)
	{
		game->SetLevel(5);
		game->GetPlayer()->SetPosition(15, 0);
		game->GetCurrentLevel()->SetDefaultPosition(15,0);
	}
	//UP
	else if (pos.y < -TILE_SIZE && game->GetCurrentLevelNumber() == 3)
	{
		game->SetLevel(7);
		game->GetPlayer()->SetPosition(14, 23);
		game->GetCurrentLevel()->SetDefaultPosition(14,23);
	}
	//LEVEL 3 TRANSITION STARTING LEVEL
	//RIGHT
	else if (pos.x > WINDOW_WIDTH * TILE_SIZE && game->GetCurrentLevelNumber() == 2)
	{
		game->SetLevel(1);
		game->GetPlayer()->SetPosition(1,4);
		game->GetCurrentLevel()->SetDefaultPosition(1,4);
	}
	//LEVEL 4 TRANSITIONS
	//UP
	else if (pos.y < -TILE_SIZE && game->GetCurrentLevelNumber() == 4)
	{
		game->SetLevel(1);
		game->GetPlayer()->SetPosition(14,23);
		game->GetCurrentLevel()->SetDefaultPosition(14,23);
	}
	//RIGHT
	else if (pos.x > WINDOW_WIDTH * TILE_SIZE && game->GetCurrentLevelNumber() == 4)
	{
		game->SetLevel(5);
		game->GetPlayer()->SetPosition(0,15);
		game->GetCurrentLevel()->SetDefaultPosition(0,15);
	}
	//LEVEL 5 TRANSITIONS
	//DOWN
	else if (pos.y > WINDOW_HEIGHT * TILE_SIZE && game->GetCurrentLevelNumber() == 5)
	{
		game->SetLevel(8);
		game->GetPlayer()->SetPosition(15, 0);
		game->GetCurrentLevel()->SetDefaultPosition(15,0);
	}
	//UP
	else if (pos.y < -TILE_SIZE && game->GetCurrentLevelNumber() == 5)
	{
		game->SetLevel(3);
		game->GetPlayer()->SetPosition(15, 23);
		game->GetCurrentLevel()->SetDefaultPosition(15,23);
	}
	//LEFT
	else if (pos.x < -TILE_SIZE && game->GetCurrentLevelNumber() == 5)
	{
		game->SetLevel(4);
		game->GetPlayer()->SetPosition(35,15);
		game->GetCurrentLevel()->SetDefaultPosition(35,15);
	}
	//LEVEL 6 TRANSITIONS
	//DOWN
	else if (pos.y > WINDOW_HEIGHT * TILE_SIZE && game->GetCurrentLevelNumber() == 6)
	{
		game->SetLevel(1);
		game->GetPlayer()->SetPosition(15,0);
		game->GetCurrentLevel()->SetDefaultPosition(15,0);
	}
	//RIGHT
	else if (pos.x > WINDOW_WIDTH * TILE_SIZE && game->GetCurrentLevelNumber() == 6)
	{
		game->SetLevel(7);
		game->GetPlayer()->SetPosition(0,10);
		game->GetCurrentLevel()->SetDefaultPosition(0,10);
	}
	//LEVEL 7 TRANSITIONS
	//LEFT
	else if (pos.x < -TILE_SIZE && game->GetCurrentLevelNumber() == 7)
	{
		game->SetLevel(6);
		game->GetPlayer()->SetPosition(35,10);
		game->GetCurrentLevel()->SetDefaultPosition(35,10);
	}
	//DOWN
	else if (pos.y > WINDOW_HEIGHT * TILE_SIZE && game->GetCurrentLevelNumber() == 7)
	{
		game->SetLevel(3);
		game->GetPlayer()->SetPosition(14, 0);
		game->GetCurrentLevel()->SetDefaultPosition(14,0);
	}
	//LEVEL 8 TRANSITIONS
	//RIGHT
	else if (pos.x > WINDOW_WIDTH * TILE_SIZE && game->GetCurrentLevelNumber() == 8)
	{
		game->SetLevel(9);
		game->GetPlayer()->SetPosition(0,8);
		game->GetCurrentLevel()->SetDefaultPosition(0,8);
	}
	//UP
	else if (pos.y < -TILE_SIZE && game->GetCurrentLevelNumber() == 8)
	{
		game->SetLevel(5);
		game->GetPlayer()->SetPosition(15, 23);
		game->GetCurrentLevel()->SetDefaultPosition(15,23);
	}
	//LEVEL 9 TRANSITIONS
	//RIGHT
	else if (pos.x < -TILE_SIZE && game->GetCurrentLevelNumber() == 9)
	{
		game->SetLevel(8);
		game->GetPlayer()->SetPosition(35,8);
		game->GetCurrentLevel()->SetDefaultPosition(35,8);
	}
}

//Change the player's sprite back to 'the blob'
void Player::ResetToPlayer()
{
	_frame = TILE_BLOB;
	_state = STATE_BLOB;
	_stepCounter = 0;
	_readyToPossess = 0;
	_accumulatedPossessTime = 0;
}

// --------------------------------------------------------------------------
// Getters
// --------------------------------------------------------------------------
int Player::GetFrame() { return _frame; }
int Player::GetState() { return _state; }
int Player::GetSteps() { return _stepCounter; }
Game * Player::GetGame() { return _theGame; }

void Player::SetFrame(int x ) { _frame = x; }

// --------------------------------------------------------------------------
// DEBUG
// Used to test levels, enables instant stop, button caused sprite change
// --------------------------------------------------------------------------
void Player::DebugMode(INPUTDATA * input)
{
	/*
	if (input->transSolider) {
		_frame = TILE_SOLDIER;
		_state = STATE_SOLDIER;
		ApproximateBlock();
	}

	if (input->transScientist) {
		_frame = TILE_SCIENTIST;
		_state = STATE_SCIENTIST;
		ApproximateBlock();
	}

	if (input->transBlob) {
		_frame = TILE_BLOB;
		_state = STATE_BLOB;
	}

	if (input->stop) {
		vel.x = 0;
		vel.y = 0;

	}*/

	if (input->reset) {
		Game::Instance()->ResetCurrentLevel();
	}

	
}