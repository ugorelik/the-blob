/***********************************************************************************
 ===================================================================================

*	File name: 		GameState.h
					===========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		A GameState is a class that is used to derive other classes. These other
		classes are different states in the game. Game is the main state where all 
		of the gameplay takes place, other examples of states include, menus,
		pausing etc.

		Uses a stack system

====================================================================================		
************************************************************************************/
#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H



class Player;
class Entity;
class GameObject;
class Level;
struct SPRITE;
struct INPUTDATA;

#include <stack>

using std::stack;

class GameState
{
	
public:

	GameState(stack<GameState *> *);
	~GameState();
	
	virtual void Input();
	virtual bool Logic(int) = 0;
	virtual void Render() = 0;
	virtual void LoadGraphics() = 0;

	// Getters
	stack<GameState *> * GetStackState();

protected:
	SPRITE * _sheet;
	INPUTDATA * _inputData;
	stack<GameState *> * _stackState;
};

#endif