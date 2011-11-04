/***********************************************************************************
 ===================================================================================

*	File name: 		Game.h
					=======

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Game < GameState
		The entry point for our game logic and the main container for it.
====================================================================================		
************************************************************************************/
#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <vector>
#include <stack>
#include <string>

class Player;
class Entity;
class GameObject;
class Level;
struct SPRITE;

using std::vector;
using std::stack;

class Game : public GameState{
private:
	static Game* _instance;
	int _currentLevel;
	float _progress;
	string _progressString;
	string _levelname;
	Player * _player;

	vector<Level *> * _levelList;
	vector<Entity *> * _entityList;
	vector<Entity *> * _enemyList;
	vector<GameObject *> * _resetList;
	vector<GameObject *> * _backgroundList;

public:

	Game(stack<GameState *> *);	
	~Game();

	virtual bool Logic(int);
	virtual void Render();
	virtual void Input();
	virtual void LoadGraphics();

	// Methods
	void AddProgress();
	void ResetCurrentLevel();

	// Getters
	Player* GetPlayer();
	vector<Entity *> * GetEnemyList();
	vector<Entity *> * GetEntityList();
	vector<GameObject *> * GetBackgroundList();
	Level * Game::GetCurrentLevel();
	int GetProgress();
	string GetProgressBar();
	string GetLevelName();

	int GetCurrentLevelNumber();

	SPRITE * GetSpriteSheet();						// Get the sprite sheet
	inline static Game * Instance(){  return _instance;   }
	
	// Setters
	void SetLevel(int);
}; 


#endif