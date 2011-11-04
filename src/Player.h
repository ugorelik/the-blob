/***********************************************************************************
 ===================================================================================

*	File name: 		Player.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		The player class controls all of the user's actions and interaction with
		the game as a sprite.
====================================================================================		
************************************************************************************/
#pragma once;
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"



#define BLOCK_MOVE_SOLDIER 4
#define BLOCK_MOVE_SCIENTIST 2
#define STATE_SOLDIER 1
#define STATE_SCIENTIST 2
#define STATE_BLOB 0
#define DECELERATION -.1
#define MAX_SPEED 7

struct INPUTDATA;

class Game;

class Player : public Entity{
private:

	int InputDataToInt(INPUTDATA *);	
	void CheckTransition();

	const float ACCELERATION;
	int _frame;
	int _state;
	int _stepCounter;
	long _accumulatedPossessTime;
	bool _readyToPossess;

	Game * _theGame;

public:
	Player(int, int, Game * game); // Constructor
	
	void ResetToPlayer();
	void Update(long time, INPUTDATA * input);
	void UpdateVelocity(INPUTDATA* input);
	void Possess(INPUTDATA *);

	void BlockMove(INPUTDATA * input);

	void DebugMode(INPUTDATA * input);
	void SetFrame(int x);

	D3DXVECTOR2 GetApproximatePosition();
	void ApproximateBlock();	// Get to the nearest tile
	void ApproximatePosition(int,int);

	// Getters
	int GetFrame();
	int GetState();
	int GetSteps();
	Game * GetGame();
};

#endif