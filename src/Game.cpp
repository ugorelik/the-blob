#include "Global.h"
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Soldier.h"
#include "Level.h"
#include "Sprite.h"
#include <sstream>
#include <algorithm>
using namespace std;

bool isDeletedPredicate(Entity * gameObject);

// Game instance
Game * Game::_instance = NULL;

Game::~Game()
{
}

	/*
	  6 7
    2 1 3
      4 5
        8 9
	*/
Game::Game(stack<GameState *> * stackState)
	: GameState(stackState)
{
	LoadGraphics();
	_progress = 0;
	_progressString = "";
	_currentLevel = 2;
	_instance = this;
	_levelList = new vector<Level *>();
	_player = new Player(1,1,this);


	_player->SetHeading(270.0f);
	_levelList->push_back(new Level(1));
	_levelList->push_back(new Level(2));
	_levelList->push_back(new Level(3));
	_levelList->push_back(new Level(4));
	_levelList->push_back(new Level(5));
	_levelList->push_back(new Level(6));
	_levelList->push_back(new Level(7));
	_levelList->push_back(new Level(8));
	_levelList->push_back(new Level(9));
	SetLevel(_currentLevel);
	_player->SetPosition(2,3);
	GetCurrentLevel()->SetDefaultPosition(15,3);

}


//////METHODS

void Game::AddProgress()
{
	_progress+= 12.5;
	std::stringstream out;
	out << _progressString;
	out << "| ";
	_progressString = out.str();
}

string Game::GetProgressBar()
{
	return _progressString;
}

string Game::GetLevelName()
{
	return _levelname;
}

// Set the lists
void Game::SetLevel(int index) {

	_currentLevel = index;
	Level * currentLevel = GetCurrentLevel();
	_backgroundList = currentLevel->GetBackgroundList();
	_entityList = currentLevel->GetEntityList();
	_enemyList = currentLevel->GetEnemyList();
	_resetList = currentLevel->GetResetList();
	_levelname = currentLevel->GetLevelName();
	
	// TODO: Set the player's current position using GetDefaultPlayerPos() from level
	// set it to the player's position
}

Level * Game::GetCurrentLevel()
{
	return _levelList->at(_currentLevel - 1);
}  

void Game::ResetCurrentLevel()
{

		Entity * curr;
		vector<Entity *>::iterator itr;
		for (itr = _enemyList->begin(); itr != _enemyList->end(); ++itr)
		{
			curr = *itr;
			delete curr;
		}

		GameObject * currObj;
		vector<GameObject *>::iterator itr2;
		for (itr2 = _resetList->begin(); itr2 != _resetList->end(); ++itr2)
		{
			currObj = *itr2;
			delete currObj;
		}

		// Clear the list
		_enemyList->clear();
		_resetList->clear();

		// Add back a new set
		GetCurrentLevel()->CreateLevel(_currentLevel);
		SetLevel(_currentLevel);
		//Reset the Player's position
		_player->ResetToPlayer();
		_player->SetPosition(GetCurrentLevel()->GetDefaultPlayerPos().x, GetCurrentLevel()->GetDefaultPlayerPos().y);
	

}

int Game::GetCurrentLevelNumber()
{
	return _currentLevel;
}

//ACCESSORS
vector<Entity *> * Game::GetEnemyList(){  return _enemyList;  }
vector<Entity *> * Game::GetEntityList(){  return _entityList;  }
vector<GameObject *> * Game::GetBackgroundList(){  return _backgroundList;  }
SPRITE * Game::GetSpriteSheet() { return _sheet; }
int Game::GetProgress() { return _progress; }
Player * Game::GetPlayer() {return _player;}


// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		RENDERER
// ======================================================================================================
void Game::Render()
{
	StartRendering();							// Direct3D.cpp

	// Render the Background
	for(int i = 0; i < _backgroundList->size(); i++) {
			GameObject * curr =_backgroundList->at(i);
			DrawSprite(_sheet,curr->GetFrame(),curr->pos.x,curr->pos.y,0, curr->GetHeading());
	}

	// Render the reset
	for(int i = 0; i < _resetList->size(); i++) {
			GameObject * curr =_resetList->at(i);
			DrawSprite(_sheet,curr->GetFrame(),curr->pos.x,curr->pos.y,0, curr->GetHeading());
	}

	// Render the Entities
	for(int i = 0; i < _entityList->size(); i++) {
		Entity * curr = _entityList->at(i);
		DrawSprite(_sheet,curr->GetFrame(),curr->pos.x,curr->pos.y,0, curr->GetHeading());
	}

	// Render the Entities
	for(int i = 0; i < _enemyList->size(); i++) {
		Entity * curr = _enemyList->at(i);
		DrawSprite(_sheet,curr->GetFrame(),curr->pos.x,curr->pos.y,0, curr->GetHeading());
	}
	
	// Render the Player
	DrawSprite(_sheet,
		_player->GetFrame(),		// Frame
		_player->pos.x,				// X pos
		_player->pos.y,				// Y Pos
		0,							// Z index
		_player->GetHeading());		// Rotation angle


	// Draw the steps
	if (_player->GetSteps() != 0){
		
		string toDraw = "Possesion Power: ";
		std::stringstream out;
		out << toDraw;
		out << _player->GetSteps();
		toDraw = out.str();
		DrawFont(0,350,600, 400, toDraw, toDraw.length());
	}

	// Draw the progress bar
	string completion = "Completion: ";
	std::stringstream out;
	out << completion;
	out << _progress;
	completion = "%";
	out << completion;
	completion = out.str();
	//DrawFont(400,100,2025, 1450, completion, completion.length());
	DrawFont(450,350,700, 650, completion, completion.length());

	string levelname;
	levelname = GetLevelName();
	DrawFont(0,0,1000,100, levelname, levelname.length());

	
	StopRendering();							// Direct3D.cpp
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
bool Game::Logic(int time)
{
	//Update Player
	_player->Update(time, _inputData);
	
	// --------------------------------------------
	// Update the Collidable trees and stuff
	vector<Entity *> * theList = _entityList; // To remove
	theList->erase(remove_if(theList->begin(), theList->end(), isDeletedPredicate), theList->end());

	// Update
	vector<Entity *>::iterator itr;
	for (itr = theList->begin(); itr != theList->end(); ++itr)
	{
		Entity * curr = *itr;
		curr->Update(time);
	}

	// --------------------------------------------
	// Update the enemies
	theList = _enemyList;
	theList->erase(remove_if(theList->begin(), theList->end(), isDeletedPredicate), theList->end());

	// Update
	for (itr = theList->begin(); itr != theList->end(); ++itr)
	{
		Entity * curr = *itr;
		curr->Update(time);
	}
	
	int midx = 0;
	int midy = 0;


	//CHECK FOR COLLISIONS
	int listSize = _entityList->size();
	for(int i = 0; i < listSize; i++){	//the player itself is element 0, which is why we start at 1
		
		
		
		Entity * curr =  _entityList->at(i);
		Player * player = _player;				// Redundant


		midx = player->pos.x + TILE_SIZE/2;
		midy = player->pos.y + TILE_SIZE/2;



		
		//Collision Code, checking player collisions
		if (
			//top left corner
			 (midx -COLLISION_BOUND > curr->pos.x) && (midx-COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy -COLLISION_BOUND> curr->pos.y) && (midy-COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		|| 
			//top right corner
		     (midx +COLLISION_BOUND > curr->pos.x) && (midx+COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy-COLLISION_BOUND > curr->pos.y) && (midy-COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		||
			 //bottom left corner
			 (midx-COLLISION_BOUND > curr->pos.x) && (midx-COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy +COLLISION_BOUND> curr->pos.y) && (midy+COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		|| 
			//bottom right corner
		     (midx +COLLISION_BOUND > curr->pos.x) && (midx+COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy +COLLISION_BOUND > curr->pos.y) && (midy +COLLISION_BOUND< curr->pos.y+TILE_SIZE) 	

		)

		{
			// There is a collision
			//PostQuitMessage(0);
			//player->SetFrame(7);
			curr->CollideAction(player);

		}
	}


	

	listSize = _enemyList->size();
	for(int i = 0; i < listSize; i++){	//the player itself is element 0, which is why we start at 1
		
		Entity * curr =  _enemyList->at(i);
		Player * player = _player;				// Redundant

		midx = player->pos.x + TILE_SIZE/2;
		midy = player->pos.y + TILE_SIZE/2;

		
		//Collision Code, checking player collisions
		if (
			//top left corner
			 (midx -COLLISION_BOUND > curr->pos.x) && (midx-COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy -COLLISION_BOUND> curr->pos.y) && (midy-COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		|| 
			//top right corner
		     (midx +COLLISION_BOUND > curr->pos.x) && (midx+COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy-COLLISION_BOUND > curr->pos.y) && (midy-COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		||
			 //bottom left corner
			 (midx-COLLISION_BOUND > curr->pos.x) && (midx-COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy +COLLISION_BOUND> curr->pos.y) && (midy+COLLISION_BOUND < curr->pos.y+TILE_SIZE) 	
		|| 
			//bottom right corner
		     (midx +COLLISION_BOUND > curr->pos.x) && (midx+COLLISION_BOUND < curr->pos.x+TILE_SIZE) &&		
			 (midy +COLLISION_BOUND > curr->pos.y) && (midy +COLLISION_BOUND< curr->pos.y+TILE_SIZE) 	

		)

		{ //Collision Detected, determine if reset



			// There is a collision
			//PostQuitMessage(0);
			//player->SetFrame(7);
			bool resetLevel = false;
			resetLevel = curr->CollideAction(player);
			
			if (resetLevel)
			{
				ResetCurrentLevel();
				break;
			}




		}
	}

	return ((int)_progress == 100);

	//return false;
}


void Game::Input()
{
	GameState::Input();
}

void Game::LoadGraphics()
{
	LoadSprite(_sheet, TEXT(TILESET_NAME), TILE_SIZE,TILE_SIZE,8,8);
	LoadFont();
	return;
}


bool isDeletedPredicate(Entity * gameObject) {
	return gameObject->FlaggedForRemove();
}